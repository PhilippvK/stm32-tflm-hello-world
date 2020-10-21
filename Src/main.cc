/**
  ******************************************************************************
  * @file           : main.cpp
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * TODO: License
  *
  * Copyright 2020 <TODO>
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include <string.h>
#include <math.h>
#include <cstdio>

/* STM32Cube Includes --------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "clock.h"

/* TFLM Includes -------------------------------------------------------------*/
#include "main_functions.h"

#ifdef BENCHMARKING
#include "benchmarking.h"
#endif /* BENCHMARKING */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define HEADBAND_HEIGHT    48

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void BSP_Init(void);
static void BSP_Welcome(void);

/* Private user code ---------------------------------------------------------*/

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
  /* Local Variables */

  /* Reset of all peripherals, Initializes interfaces and Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();

  MX_UART_Init();

  /* Setup BSP Components */
  BSP_Init();

  /* Show Welcome Screen */
  BSP_Welcome();

  /* Infinite loop */
  fprintf(stderr, "--- TFLM Demo for STM32 Boards ---\n\r");
  setup();
  fprintf(stderr, "Setup done! Main loop starts now!\n\r");
  while (true) {
    loop();
#ifdef HELLO_WOLRD_DELAY_MS
    HAL_Delay(HELLO_WOLRD_DELAY_MS);
#endif /* HELLO_WOLRD_DELAY_MS */

#ifdef BENCHMARKING
    print_summary(TICKS_POPULATE|TICKS_INVOKE|TICKS_RESPOND);
#endif /* BENCHMARKING */
  }

  return 0;
}


/**
  * @brief TODO
  * @retval uint8_t (1 when button clicked)
  *
  */
uint8_t CheckForUserInput(void) {
  if (BSP_PB_GetState(BUTTON_WAKEUP) != GPIO_PIN_RESET) {
    while (BSP_PB_GetState(BUTTON_WAKEUP) != GPIO_PIN_RESET) {}
    return 1;
  }
  return 0;
}

/**
  * @brief Board Support Package Initialization
  * @retval None
  *
  */
static void BSP_Init(void) {
  /* Configure LEDs */
  BSP_LED_Init(LED_GREEN);
  BSP_LED_Init(LED_RED);
  BSP_LED_On(LED_GREEN);

  /* Configure Button */
  BSP_PB_Init(BUTTON_WAKEUP, BUTTON_MODE_GPIO);
  /* Configure LCD */
  /* Initialize the LCD */
  uint8_t  lcd_status = LCD_OK;
  lcd_status = BSP_LCD_Init();
  while (lcd_status != LCD_OK) {}
#ifdef STM32_BOARD_STM32F769I_DISCOVERY
  BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);
#endif /* STM32_BOARD_STM32F769I_DISCOVERY */
  BSP_LCD_Clear(LCD_COLOR_WHITE);

  /* Configure Touchscreen (optional) */
  // Touchscreen_Calibration();
  BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());

  /* Set Default LCD Colors and Fonts */
  BSP_LCD_Clear(LCD_COLOR_WHITE);
  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
  BSP_LCD_SetFont(&Font12);
}

/**
  * @brief Show Welcome Message on LCD
  * @retval None
  *
  */
static void BSP_Welcome() {
  /* Local Variables */
  const uint16_t delay_ms = 1000;

  /* Save old Display Configuration */
  sFONT* old_font = BSP_LCD_GetFont();
  uint32_t old_text_color = BSP_LCD_GetTextColor();
  uint32_t old_back_color = BSP_LCD_GetTextColor();
  char str[32];

  /* Clear the LCD */
  BSP_LCD_Clear(LCD_COLOR_WHITE);

  /* Draw Banner */
  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
  BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), HEADBAND_HEIGHT);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_SetBackColor(LCD_COLOR_BLUE);

  /* Add Text to banner */
  BSP_LCD_SetFont(&Font16);
  BSP_LCD_DisplayStringAt(0, 5, (uint8_t *)"TFLM Demo", CENTER_MODE);
  BSP_LCD_SetFont(&Font12);
  BSP_LCD_DisplayStringAt(0, 25, (uint8_t *)"for STM32 Boards", CENTER_MODE);
  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
  BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
  sprintf(str, "Board: %16s", TFLM_BOARD);  // TODO(PhilippvK): Use snprintf
  BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()/2-20, (uint8_t *)str,
                          CENTER_MODE);
  sprintf(str, "Example: %16s", TFLM_EXAMPLE);  // TODO(PhilippvK): snprintf
  BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()/2+10, (uint8_t *)str,
                          CENTER_MODE);

  /* Wait a moment */
  HAL_Delay(delay_ms);

  /* Restore Font and Colors*/
  BSP_LCD_SetTextColor(old_text_color);
  BSP_LCD_SetBackColor(old_back_color);
  BSP_LCD_SetFont(old_font);
}

/**
  * @brief  Function used by printf tto write to the serial terminal
  * @retval int
  */
int __io_putchar(int ch) {
  HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void) {
  /* User can add his own implementation to report the HAL error return state */
  fprintf(stderr, "Error_Handler called! Waiting for reset...\n\r");
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line) {
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */
