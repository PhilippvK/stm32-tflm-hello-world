/* Copyright 2020 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Modifications by @PhilippvK:
- Support tflite_micro_compiler by defining `TFLM_MODE_COMPILER`
  See: https://github.com/tum-ei-eda/tflite_micro_compiler
- Support Benchmarking by defining `BENCHMARKING`
  See: https://github.com/PhilippvK/stm32-tflm-benchmarking
- Changed formatting according to cpplint

==============================================================================*/


#include "main_functions.h"

#ifdef TFLM_MODE_COMPILER
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "constants.h"
#include "output_handler.h"
#include "offline_model.h"
#else
#include "tensorflow/lite/micro/micro_error_reporter.h"
#ifdef MEMORY_REPORTING
#include "tensorflow/lite/micro/recording_micro_interpreter.h"
#else
#include "tensorflow/lite/micro/micro_interpreter.h"
#endif /* MEMORY_REPORTING */
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "constants.h"
#include "model_data.h"
#include "output_handler.h"
#endif /* TFLM_MODE_COMPILER */

#ifdef BENCHMARKING
#include "benchmarking.h"
#endif /* BENCHMARKING */

// Globals, used for compatibility with Arduino-style sketches.
namespace {
tflite::ErrorReporter* error_reporter = nullptr;
#ifndef TFLM_MODE_COMPILER
const tflite::Model* model = nullptr;
#ifdef MEMORY_REPORTING
tflite::RecordingMicroInterpreter* interpreter = nullptr;
#else
tflite::MicroInterpreter* interpreter = nullptr;
#endif /* MEMORY_REPORTING */
TfLiteTensor* input = nullptr;
TfLiteTensor* output = nullptr;
#endif /* TFLM_MODE_COMPILER */
int inference_count = 0;

#ifndef TFLM_MODE_COMPILER
// Create an area of memory to use for input, output, and intermediate arrays.
// Minimum arena size, at the time of writing. After allocating tensors
// you can retrieve this value by invoking interpreter.arena_used_bytes().
const int kModelArenaSize = 2468;
// Extra headroom for model + alignment + future interpreter changes.
const int kExtraArenaSize = 560 + 16 + 100;
const int kTensorArenaSize = kModelArenaSize + kExtraArenaSize;
uint8_t tensor_arena[kTensorArenaSize];
#endif /* TFLM_MODE_COMPILER */
}  // namespace

// The name of this function is important for Arduino compatibility.
void setup() {
  // Set up logging. Google style is to avoid globals or statics because of
  // lifetime uncertainty, but since this has a trivial destructor it's okay.
  // NOLINTNEXTLINE(runtime-global-variables)
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

#ifdef TFLM_MODE_COMPILER
  hello_world_init();
#else
  // Map the model into a usable data structure. This doesn't involve any
  // copying or parsing, it's a very lightweight operation.
  model = tflite::GetModel(g_model);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    TF_LITE_REPORT_ERROR(error_reporter,
                         "Model provided is schema version %d not equal "
                         "to supported version %d.",
                         model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }

  // This pulls in all the operation implementations we need.
  // NOLINTNEXTLINE(runtime-global-variables)
  static tflite::AllOpsResolver resolver;

  // Build an interpreter to run the model with.
#ifdef MEMORY_REPORTING
  static tflite::RecordingMicroInterpreter static_interpreter(
      model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
#else
  static tflite::MicroInterpreter static_interpreter(
      model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
#endif /* MEMORY_REPORTING */
  interpreter = &static_interpreter;

  // Allocate memory from the tensor_arena for the model's tensors.
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "AllocateTensors() failed");
    return;
  }

  // Obtain pointers to the model's input and output tensors.
  input = interpreter->input(0);
  output = interpreter->output(0);
#endif /* TFLM_MODE_COMPILER */

  // Keep track of how many inferences we have performed.
  inference_count = 0;
}

// The name of this function is important for Arduino compatibility.
void loop() {
  // Calculate an x value to feed into the model. We compare the current
  // inference_count to the number of inferences per cycle to determine
  // our position within the range of possible x values the model was
  // trained on, and use this to calculate a value.
#ifdef BENCHMARKING
  uint32_t ticks_before, ticks_after;
  ticks_before = HAL_GetTick();
#endif /* BENCHMARKING */
  float position = static_cast<float>(inference_count) /
                   static_cast<float>(kInferencesPerCycle);
  float x_val = position * kXrange;

  // Place our calculated x value in the model's input tensor
#ifdef TFLM_MODE_COMPILER
  tflite::GetTensorData<float>(hello_world_input(0))[0] = x_val;
#else
  input->data.f[0] = x_val;
#endif /* TFLM_MODE_COMPILER */
#ifdef BENCHMARKING
  ticks_after = HAL_GetTick();
  update_avg_ticks(TICKS_POPULATE, (int32_t)(ticks_after-ticks_before));
#endif /* BENCHMARKING */

  // Run inference, and report any error
#ifdef BENCHMARKING
  ticks_before = HAL_GetTick();
#endif /* BENCHMARKING */
#ifdef TFLM_MODE_COMPILER
  hello_world_invoke();
#else
  TfLiteStatus invoke_status = interpreter->Invoke();
  if (invoke_status != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "Invoke failed on x_val: %f\n",
                         static_cast<double>(x_val));
    return;
  }
#endif /* TFLM_MODE_COMPILER */
#ifdef BENCHMARKING
  ticks_after = HAL_GetTick();
  update_avg_ticks(TICKS_INVOKE, (int32_t)(ticks_after-ticks_before));
#endif /* BENCHMARKING */

  // Read the predicted y value from the model's output tensor
#ifdef BENCHMARKING
  ticks_before = HAL_GetTick();
#endif /* BENCHMARKING */
#ifdef TFLM_MODE_COMPILER
  float y_val = tflite::GetTensorData<float>(hello_world_output(0))[0];
#else
  float y_val = output->data.f[0];
#ifdef MEMORY_REPORTING
  // Print out detailed allocation information:
  interpreter->GetMicroAllocator().PrintAllocations();
#endif /* MEMORY_REPORTING */
#endif /* TFLM_MODE_COMPILER */

  // Output the results. A custom HandleOutput function can be implemented
  // for each supported hardware target.
  HandleOutput(error_reporter, x_val, y_val);

  // Increment the inference_counter, and reset it if we have reached
  // the total number per cycle
  inference_count += 1;
  if (inference_count >= kInferencesPerCycle) inference_count = 0;
#ifdef BENCHMARKING
  ticks_after = HAL_GetTick();
  update_avg_ticks(TICKS_RESPOND, (int32_t)(ticks_after-ticks_before));
#endif /* BENCHMARKING */
}
