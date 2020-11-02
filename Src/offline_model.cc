// This file is generated. Do not edit.
// Generated on: 02.11.2020 15:58:51

#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/micro/kernels/fully_connected.h"
#include "tensorflow/lite/micro/kernels/micro_ops.h"

#if defined __GNUC__
#define ALIGN(X) __attribute__((aligned(X)))
#elif defined _MSC_VER
#define ALIGN(X) __declspec(align(X))
#elif defined __TASKING__
#define ALIGN(X) __align(X)
#endif

namespace {

constexpr int kTensorArenaSize = 224;
uint8_t tensor_arena[kTensorArenaSize] ALIGN(16);
template <int SZ, class T> struct TfArray {
  int sz; T elem[SZ];
};
enum used_operators_e {
  OP_FULLY_CONNECTED,  OP_LAST
};
struct TensorInfo_t { // subset of TfLiteTensor used for initialization from constant memory
  void* data;
  TfLiteIntArray* dims;
  size_t bytes;
};
struct NodeInfo_t { // subset of TfLiteNode used for initialization from constant memory
  struct TfLiteIntArray* inputs;
  struct TfLiteIntArray* outputs;
  void* builtin_data;
  used_operators_e used_op_index;
};

TfLiteContext ctx{};
TfLiteTensor tflTensors[10];
TfLiteEvalTensor evalTensors[10];
TfLiteRegistration registrations[OP_LAST];
TfLiteNode tflNodes[3];

const TfArray<2, int> tensor_dimension0 = { 2, { 1,1 } };
const TfArray<2, int> tensor_dimension1 = { 2, { 1,1 } };
const ALIGN(8) float tensor_data2[16*1] = { 
  0.48572906851768494, 
  0.11921578645706177, 
  0.071446508169174194, 
  -0.12941524386405945, 
  0.050381854176521301, 
  -0.53648358583450317, 
  -0.38303017616271973, 
  0.28105074167251587, 
  -0.0096142292022705078, 
  -0.18292877078056335, 
  -0.18201220035552979, 
  -0.3307003378868103, 
  0.40724596381187439, 
  0.50172483921051025, 
  0.10627789795398712, 
  -0.14003723859786987, 
};
const TfArray<2, int> tensor_dimension2 = { 2, { 16,1 } };
const ALIGN(8) float tensor_data3[16] = { 
    8.3092876593582332e-05, 0.30068591237068176, -0.25840592384338379, 0, 0.3217712938785553, 0, 0, 0.14898249506950378, 0, 0, 
    0.87438428401947021, 0, 0.20114737749099731, -0.2935253381729126, -0.41638386249542236, 0, 
};
const TfArray<1, int> tensor_dimension3 = { 1, { 16 } };
const TfArray<2, int> tensor_dimension4 = { 2, { 1,16 } };
const ALIGN(8) float tensor_data5[16*16] = { 
  -0.22823916375637054, -0.052720785140991211, -0.0058372914791107178, -0.25366902351379395, 0.060682415962219238, 0.28659388422966003, -0.21606582403182983, -0.25502443313598633, -0.33390569686889648, -0.10099118947982788, 0.035239458084106445, 0.015801131725311279, 0.0022124946117401123, -0.080068409442901611, -0.096374988555908203, -0.13718682527542114, 
  -0.48115906119346619, -0.26873311400413513, 0.49225515127182007, 0.25006929039955139, -0.21498270332813263, -0.42953398823738098, -0.38514730334281921, -0.48115560412406921, -0.20412549376487732, -0.42450016736984253, 0.63544374704360962, 0.077878743410110474, 0.018004059791564941, -0.33819782733917236, -0.22588138282299042, -0.08642241358757019, 
  0.0021735026966780424, 0.27672755718231201, 0.087675966322422028, -0.40909197926521301, -0.021604467183351517, -0.016229867935180664, -0.29218113422393799, 0.069244325160980225, -0.3220219612121582, -0.21818222105503082, -1.6236565113067627, 0.3447054922580719, 0.30335775017738342, -0.28669315576553345, -0.68688112497329712, 0.007964015007019043, 
  0.18796414136886597, -0.0033005243167281151, -0.47314673662185669, -0.1153315007686615, 0.17493326961994171, -0.25703942775726318, 0.23521909117698669, 0.38866889476776123, 0.050147384405136108, 0.24008336663246155, -0.99463868141174316, -0.32450515031814575, -0.035067390650510788, 0.076039649546146393, -0.88431704044342041, -0.4052760899066925, 
  0.15902571380138397, -0.24998345971107483, -0.20162467658519745, -0.42761632800102234, -0.26561912894248962, -0.11129167675971985, 0.066945672035217285, 0.48230233788490295, 0.32554164528846741, -0.35316985845565796, 1.4257353544235229, 0.32904770970344543, -0.27501446008682251, 0.37898632884025574, 0.669150710105896, -0.42291000485420227, 
  0.32231584191322327, -0.16388630867004395, -0.19437515735626221, 0.31877788901329041, 0.18518862128257751, 0.035534828901290894, 0.34623393416404724, -0.39122298359870911, -0.42959931492805481, 0.24439278244972229, -0.12590217590332031, 0.31687274575233459, -0.015886932611465454, -0.12637355923652649, 0.33516028523445129, 0.29952415823936462, 
  -0.19679814577102661, 0.35512396693229675, -0.47684523463249207, 0.33757057785987854, 0.33560457825660706, 0.40986540913581848, -0.33875325322151184, 0.32362434267997742, -0.13870257139205933, -0.0066515505313873291, -1.3480823040008545, 0.14057376980781555, 0.00089796201791614294, 0.0060705011710524559, -0.63653659820556641, -0.42781618237495422, 
  0.16377024352550507, -0.11972510069608688, 0.27099522948265076, -0.36326780915260315, -0.24160611629486084, -0.049308866262435913, 0.17075857520103455, -0.29670268297195435, -0.069954454898834229, -0.25903069972991943, 1.181910514831543, -0.046306401491165161, 0.36786362528800964, 0.023215260356664658, 1.1258401870727539, -0.37561273574829102, 
  -0.40739616751670837, -0.14968851208686829, 0.26288127899169922, -0.25091266632080078, -0.09480990469455719, -0.0058791041374206543, 0.24520525336265564, 0.065009057521820068, -0.25441205501556396, 0.15379932522773743, 0.36172431707382202, 0.25531330704689026, 0.15808242559432983, -0.29907789826393127, 0.13371126353740692, -0.15105608105659485, 
  0.31234276294708252, -0.0023092026822268963, -0.51812952756881714, 0.059237509965896606, 0.4929262101650238, 0.030715048313140869, 0.26449748873710632, -0.28747206926345825, -0.27947291731834412, 0.027822107076644897, -1.2957823276519775, -0.0052262246608734131, 0.15189048647880554, -0.079709775745868683, -0.29195484519004822, -0.28377443552017212, 
  -0.031022831797599792, 0.0088589880615472794, 0.25614765286445618, -0.044026672840118408, 0.1464834064245224, 0.022341996431350708, -0.20924550294876099, -0.21239104866981506, 0.076928824186325073, -0.22963133454322815, 0.0067050582729279995, 0.16723206639289856, 0.075782865285873413, -0.3221430778503418, -0.11913619190454483, 0.21264305710792542, 
  -0.13428838551044464, 0.12832707166671753, -0.092646405100822449, -0.1946103423833847, 0.44356217980384827, -0.015184283256530762, 0.17192736268043518, -0.18117105960845947, -0.25724232196807861, 0.22180286049842834, 0.48073673248291016, 0.36643216013908386, -0.18375381827354431, -0.28309127688407898, 0.51496416330337524, 0.30512455105781555, 
  -0.40692901611328125, -0.059139847755432129, -0.164735347032547, -0.15186402201652527, 0.05970466136932373, 0.36014679074287415, 0.37111476063728333, -0.059040099382400513, -0.042262226343154907, 0.37717226147651672, -0.052400559186935425, 0.21940329670906067, -0.3060566782951355, 0.082838088274002075, 0.11403349041938782, 0.041466683149337769, 
  0.22487232089042664, -0.17295259237289429, 0.67364424467086792, -0.068747490644454956, -0.45097881555557251, 0.34799399971961975, -0.086766183376312256, -0.21128953993320465, -0.16684171557426453, -0.32129546999931335, 1.4172621965408325, 0.15223154425621033, 0.36632111668586731, -0.0017640921287238598, 0.86176145076751709, -0.03955647349357605, 
  0.17065231502056122, -0.1960889995098114, 0.12822848558425903, 0.321218341588974, 0.33064335584640503, -0.070652961730957031, -0.40995854139328003, 0.31311541795730591, 0.3864503800868988, 0.24506071209907532, 0.70417290925979614, 0.35802218317985535, 0.22638307511806488, -0.25871041417121887, 0.74499732255935669, 0.14788058400154114, 
  -0.93977910280227661, -0.6756054162979126, -0.32675075531005859, 0.23668220639228821, -0.11429153382778168, -0.26789361238479614, -0.188725546002388, 0.064689792692661285, 0.34829649329185486, -0.07605355978012085, 0.31624582409858704, -0.34355002641677856, -0.25043568015098572, -0.63066196441650391, 0.15290027856826782, -0.15751197934150696, 
};
const TfArray<2, int> tensor_dimension5 = { 2, { 16,16 } };
const ALIGN(8) float tensor_data6[16] = { 
    0, 0.1947588175535202, 0.41492420434951782, 0.24981175363063812, -0.3031541109085083, 0, 0.42656701803207397, -0.30534753203392029, 0.19173803925514221, 0.39573973417282104, 
    -0.067452907562255859, 0.18677203357219696, 0, -0.32674875855445862, -0.26730072498321533, 0.21889102458953857, 
};
const TfArray<1, int> tensor_dimension6 = { 1, { 16 } };
const TfArray<2, int> tensor_dimension7 = { 2, { 1,16 } };
const ALIGN(8) float tensor_data8[1*16] = { 
  0.27896255254745483, -0.80062443017959595, -0.98235404491424561, -0.46473497152328491, 0.80508893728256226, 0.24268072843551636, -0.42904683947563171, 0.55626356601715088, -0.82673227787017822, -0.43692430853843689, 0.27155888080596924, -0.67535167932510376, -0.28081029653549194, 0.70761901140213013, 0.40235647559165955, -1.0791106224060059, 
};
const TfArray<2, int> tensor_dimension8 = { 2, { 1,16 } };
const ALIGN(4) float tensor_data9[1] = { 
    -0.21645687520503998, 
};
const TfArray<1, int> tensor_dimension9 = { 1, { 1 } };
const TfLiteFullyConnectedParams opdata0 = { kTfLiteActRelu, kTfLiteFullyConnectedWeightsFormatDefault, false, false };
const TfArray<3, int> inputs0 = { 3, { 1,2,3 } };
const TfArray<1, int> outputs0 = { 1, { 4 } };
const TfLiteFullyConnectedParams opdata1 = { kTfLiteActRelu, kTfLiteFullyConnectedWeightsFormatDefault, false, false };
const TfArray<3, int> inputs1 = { 3, { 4,5,6 } };
const TfArray<1, int> outputs1 = { 1, { 7 } };
const TfLiteFullyConnectedParams opdata2 = { kTfLiteActNone, kTfLiteFullyConnectedWeightsFormatDefault, false, false };
const TfArray<3, int> inputs2 = { 3, { 7,8,9 } };
const TfArray<1, int> outputs2 = { 1, { 0 } };
const TensorInfo_t tensorData[] = {
  { tensor_arena + 64, (TfLiteIntArray*)&tensor_dimension0, 4, },
  { tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension1, 4, },
  { (void*)tensor_data2, (TfLiteIntArray*)&tensor_dimension2, 64, },
  { (void*)tensor_data3, (TfLiteIntArray*)&tensor_dimension3, 64, },
  { tensor_arena + 64, (TfLiteIntArray*)&tensor_dimension4, 64, },
  { (void*)tensor_data5, (TfLiteIntArray*)&tensor_dimension5, 1024, },
  { (void*)tensor_data6, (TfLiteIntArray*)&tensor_dimension6, 64, },
  { tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension7, 64, },
  { (void*)tensor_data8, (TfLiteIntArray*)&tensor_dimension8, 64, },
  { (void*)tensor_data9, (TfLiteIntArray*)&tensor_dimension9, 4, },
};
const NodeInfo_t nodeData[] = {
  { (TfLiteIntArray*)&inputs0, (TfLiteIntArray*)&outputs0, const_cast<void*>(static_cast<const void*>(&opdata0)), OP_FULLY_CONNECTED, },
  { (TfLiteIntArray*)&inputs1, (TfLiteIntArray*)&outputs1, const_cast<void*>(static_cast<const void*>(&opdata1)), OP_FULLY_CONNECTED, },
  { (TfLiteIntArray*)&inputs2, (TfLiteIntArray*)&outputs2, const_cast<void*>(static_cast<const void*>(&opdata2)), OP_FULLY_CONNECTED, },
};
static void* AllocatePersistentBuffer(struct TfLiteContext* ctx,
                                                 size_t bytes) {
  static uint8_t *AllocPtr = tensor_arena + sizeof(tensor_arena);

  AllocPtr -= bytes;
  return AllocPtr;
}

static TfLiteEvalTensor *GetEvalTensor(const struct TfLiteContext *context,
                                       int tensor_idx) {
  return &evalTensors[tensor_idx];
}
} // namespace

TfLiteStatus hello_world_init() {
  ctx.AllocatePersistentBuffer = &AllocatePersistentBuffer;
  ctx.GetEvalTensor = &GetEvalTensor;
  ctx.tensors = tflTensors;
  ctx.tensors_size = 10;
  for(size_t i = 0; i < 10; ++i) {
    tflTensors[i].data.data = tensorData[i].data;
    evalTensors[i].data.data = tensorData[i].data;
    tflTensors[i].type = kTfLiteFloat32;
    evalTensors[i].type = kTfLiteFloat32;
    tflTensors[i].is_variable = 0;
    tflTensors[i].allocation_type = (tensor_arena <= tensorData[i].data && tensorData[i].data < tensor_arena + kTensorArenaSize) ? kTfLiteArenaRw : kTfLiteMmapRo;
    tflTensors[i].bytes = tensorData[i].bytes;
    tflTensors[i].dims = tensorData[i].dims;
    evalTensors[i].dims = tensorData[i].dims;
    tflTensors[i].quantization.type = kTfLiteNoQuantization;
  }
  registrations[OP_FULLY_CONNECTED] = tflite::Register_FULLY_CONNECTED();

  for(size_t i = 0; i < 3; ++i) {
    tflNodes[i].inputs = nodeData[i].inputs;
    tflNodes[i].outputs = nodeData[i].outputs;
    tflNodes[i].builtin_data = nodeData[i].builtin_data;
    tflNodes[i].custom_initial_data = nullptr;
    tflNodes[i].custom_initial_data_size = 0;
    if (registrations[nodeData[i].used_op_index].init) {
      tflNodes[i].user_data = registrations[nodeData[i].used_op_index].init(&ctx, (const char*)tflNodes[i].builtin_data, 0);
    }
  }
  for(size_t i = 0; i < 3; ++i) {
    if (registrations[nodeData[i].used_op_index].prepare) {
      TfLiteStatus status = registrations[nodeData[i].used_op_index].prepare(&ctx, &tflNodes[i]);
      if (status != kTfLiteOk) {
        return status;
      }
    }
  }
  return kTfLiteOk;
}

static const int inTensorIndices[] = {
  1, 
};
TfLiteTensor* hello_world_input(int index) {
  return &ctx.tensors[inTensorIndices[index]];
}

static const int outTensorIndices[] = {
  0, 
};
TfLiteTensor* hello_world_output(int index) {
  return &ctx.tensors[outTensorIndices[index]];
}

TfLiteStatus hello_world_invoke() {
  for(size_t i = 0; i < 3; ++i) {
    TfLiteStatus status = registrations[nodeData[i].used_op_index].invoke(&ctx, &tflNodes[i]);
    if (status != kTfLiteOk) {
      return status;
    }
  }
  return kTfLiteOk;
}
