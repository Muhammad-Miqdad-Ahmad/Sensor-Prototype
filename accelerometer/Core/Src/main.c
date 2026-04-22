/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include "ai_datatypes_defines.h"
#include "ai_platform.h"
#include "sine.h"
#include "sine_data.h"
#include "stm32l4xx_hal_uart.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/_intsup.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CRC_HandleTypeDef hcrc;

I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
LSM6DSL_Object_t MotionSensor;
volatile uint32_t dataRdyIntReceived;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_CRC_Init(void);
/* USER CODE BEGIN PFP */
static void MEMS_Init(void);
int _write(int fd, char *ptr, int len);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

  /* USER CODE BEGIN 1 */
  ai_error ai_err;
  ai_i32 nbatch;
  float y_val;

  AI_ALIGNED(4) ai_u8 activations[AI_SINE_DATA_ACTIVATIONS_SIZE];

  AI_ALIGNED(4) ai_i8 in_data[AI_SINE_IN_1_SIZE_BYTES];
  AI_ALIGNED(4) ai_i8 out_data[AI_SINE_OUT_1_SIZE_BYTES];

  ai_handle sine = AI_HANDLE_NULL;

  ai_buffer ai_input[AI_SINE_IN_NUM] = AI_SINE_IN;
  ai_buffer ai_output[AI_SINE_OUT_NUM] = AI_SINE_OUT;

  ai_network_params ai_params = {
      AI_SINE_DATA_WEIGHTS(ai_sine_data_weights_get()),
      AI_SINE_DATA_ACTIVATIONS(activations)};

  ai_input[0].n_batches = 1;
  ai_input[0].data = AI_HANDLE_PTR(in_data);
  ai_output[0].n_batches = 1;
  ai_output[0].data = AI_HANDLE_PTR(out_data);

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick.
   */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_CRC_Init();
  /* USER CODE BEGIN 2 */

  dataRdyIntReceived = 0;
  // For the inbuilt accelerometer
  MEMS_Init();

  // The lcd library init
  ssd1306_Init();

  // Clearing the screen
  ssd1306_Fill(Black);
  // actually applies the changes to the screen
  ssd1306_UpdateScreen();

  ssd1306_SetCursor(0, 0);
  ssd1306_WriteString("HELLO", Font_11x18, White);

  ssd1306_SetCursor(0, 30);
  ssd1306_WriteString("LED working now", Font_7x10, White);

  ssd1306_UpdateScreen();
  HAL_Delay(1000);

  printf("Lets see what is going on");

  ai_err = ai_sine_create(&sine, AI_SINE_DATA_CONFIG);

  if (ai_err.type != AI_ERROR_NONE) {
    printf("Error: could not create NN instance\r\n");
    while (1)
      ;
  }

  if (!ai_sine_init(sine, &ai_params)) {
    printf("Error: could not create initialize the model\r\n");
    while (1)
      ;
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {
    /* USER CODE END WHILE */

    for (uint32_t i = 0; i < AI_SINE_IN_1_SIZE; i++) {
      ((ai_float *)in_data)[0] = (ai_float)2.0f;
    }

    nbatch = ai_sine_run(sine, &ai_input[0], &ai_output[0]);
    if (nbatch != 1) {
      printf("Error: Could not run inference");
    }

    y_val = ((float *)out_data)[0];
    printf("The Value is: %f", y_val);

    //! FOr now Imma gonna comment all the lcd and the accelerometer and gyro
    //! outputs
    // if (dataRdyIntReceived != 0) {
    //   // CLear the LCD
    //   ssd1306_Fill(Black);

    //   dataRdyIntReceived = 0;

    //   // Get the accelerometer values
    //   LSM6DSL_Axes_t acc_axes, gyro_axes;
    //   LSM6DSL_ACC_GetAxes(&MotionSensor, &acc_axes);
    //   LSM6DSL_GYRO_GetAxes(&MotionSensor, &gyro_axes);

    //   printf("Accelerometer: % 5d, % 5d, % 5d\r\n", acc_axes.x, acc_axes.y,
    //          acc_axes.z);
    //   printf("Gyro Scope: % 5d, % 5d, % 5d\r\n", gyro_axes.x, gyro_axes.y,
    //          gyro_axes.z);

    //   char buffer[32];

    //   sprintf(buffer, "X: %d", acc_axes.x);
    //   ssd1306_SetCursor(0, 0);
    //   ssd1306_WriteString(buffer, Font_7x10, White);

    //   sprintf(buffer, "Y: %d", acc_axes.y);
    //   ssd1306_SetCursor(0, 10);
    //   ssd1306_WriteString(buffer, Font_7x10, White);

    //   sprintf(buffer, "Z: %d", acc_axes.z);
    //   ssd1306_SetCursor(0, 20);
    //   ssd1306_WriteString(buffer, Font_7x10, White);
    //   sprintf(buffer, "X: %d", gyro_axes.x);

    //   ssd1306_SetCursor(0, 33);
    //   ssd1306_WriteString(buffer, Font_7x10, White);

    //   sprintf(buffer, "Y: %d", gyro_axes.y);
    //   ssd1306_SetCursor(0, 43);
    //   ssd1306_WriteString(buffer, Font_7x10, White);

    //   sprintf(buffer, "Z: %d", gyro_axes.z);
    //   ssd1306_SetCursor(0, 53);
    //   ssd1306_WriteString(buffer, Font_7x10, White);

    //   ssd1306_UpdateScreen();

    //   HAL_Delay(100);
    // } else {
    //   printf("No Data to display\n");
    //   ssd1306_Fill(Black);
    //   ssd1306_SetCursor(0, 0);
    //   ssd1306_WriteString("Error", Font_7x10, White);
    //   ssd1306_UpdateScreen();
    //   dataRdyIntReceived = 1;
    // }
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
   */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
    Error_Handler();
  }
}

/**
 * @brief CRC Initialization Function
 * @param None
 * @retval None
 */
static void MX_CRC_Init(void) {

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
  hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
  hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
  hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
  hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
  if (HAL_CRC_Init(&hcrc) != HAL_OK) {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */
}

/**
 * @brief I2C1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C1_Init(void) {

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x10D19CE4;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
    Error_Handler();
  }

  /** Configure Analogue filter
   */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK) {
    Error_Handler();
  }

  /** Configure Digital filter
   */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK) {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */
}

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void) {

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK) {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(
      GPIOE, M24SR64_Y_RF_DISABLE_Pin | M24SR64_Y_GPO_Pin | ISM43362_RST_Pin,
      GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ARD_D10_Pin | SPBTLE_RF_RST_Pin | ARD_D9_Pin,
                    GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB,
                    ARD_D8_Pin | ISM43362_BOOT0_Pin | ISM43362_WAKEUP_Pin |
                        LED2_Pin | SPSGRF_915_SDN_Pin | ARD_D5_Pin,
                    GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(
      GPIOD, USB_OTG_FS_PWR_EN_Pin | PMOD_RESET_Pin | STSAFE_A100_RESET_Pin,
      GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPBTLE_RF_SPI3_CSN_GPIO_Port, SPBTLE_RF_SPI3_CSN_Pin,
                    GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, VL53L0X_XSHUT_Pin | LED3_WIFI__LED4_BLE_Pin,
                    GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPSGRF_915_SPI3_CSN_GPIO_Port, SPSGRF_915_SPI3_CSN_Pin,
                    GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ISM43362_SPI3_CSN_GPIO_Port, ISM43362_SPI3_CSN_Pin,
                    GPIO_PIN_SET);

  /*Configure GPIO pins : M24SR64_Y_RF_DISABLE_Pin M24SR64_Y_GPO_Pin
   * ISM43362_RST_Pin ISM43362_SPI3_CSN_Pin */
  GPIO_InitStruct.Pin = M24SR64_Y_RF_DISABLE_Pin | M24SR64_Y_GPO_Pin |
                        ISM43362_RST_Pin | ISM43362_SPI3_CSN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : USB_OTG_FS_OVRCR_EXTI3_Pin SPSGRF_915_GPIO3_EXTI5_Pin
   * SPBTLE_RF_IRQ_EXTI6_Pin ISM43362_DRDY_EXTI1_Pin */
  GPIO_InitStruct.Pin = USB_OTG_FS_OVRCR_EXTI3_Pin |
                        SPSGRF_915_GPIO3_EXTI5_Pin | SPBTLE_RF_IRQ_EXTI6_Pin |
                        ISM43362_DRDY_EXTI1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : BUTTON_EXTI13_Pin */
  GPIO_InitStruct.Pin = BUTTON_EXTI13_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BUTTON_EXTI13_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ARD_A5_Pin ARD_A4_Pin ARD_A3_Pin ARD_A2_Pin
                           ARD_A1_Pin ARD_A0_Pin */
  GPIO_InitStruct.Pin = ARD_A5_Pin | ARD_A4_Pin | ARD_A3_Pin | ARD_A2_Pin |
                        ARD_A1_Pin | ARD_A0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG_ADC_CONTROL;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : ARD_D1_Pin ARD_D0_Pin */
  GPIO_InitStruct.Pin = ARD_D1_Pin | ARD_D0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : ARD_D10_Pin SPBTLE_RF_RST_Pin ARD_D9_Pin */
  GPIO_InitStruct.Pin = ARD_D10_Pin | SPBTLE_RF_RST_Pin | ARD_D9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : ARD_D4_Pin */
  GPIO_InitStruct.Pin = ARD_D4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
  HAL_GPIO_Init(ARD_D4_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ARD_D7_Pin */
  GPIO_InitStruct.Pin = ARD_D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG_ADC_CONTROL;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ARD_D7_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ARD_D13_Pin ARD_D12_Pin ARD_D11_Pin */
  GPIO_InitStruct.Pin = ARD_D13_Pin | ARD_D12_Pin | ARD_D11_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : ARD_D3_Pin */
  GPIO_InitStruct.Pin = ARD_D3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ARD_D3_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ARD_D6_Pin */
  GPIO_InitStruct.Pin = ARD_D6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG_ADC_CONTROL;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ARD_D6_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ARD_D8_Pin ISM43362_BOOT0_Pin ISM43362_WAKEUP_Pin
     LED2_Pin SPSGRF_915_SDN_Pin ARD_D5_Pin SPSGRF_915_SPI3_CSN_Pin */
  GPIO_InitStruct.Pin = ARD_D8_Pin | ISM43362_BOOT0_Pin | ISM43362_WAKEUP_Pin |
                        LED2_Pin | SPSGRF_915_SDN_Pin | ARD_D5_Pin |
                        SPSGRF_915_SPI3_CSN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : DFSDM1_DATIN2_Pin DFSDM1_CKOUT_Pin */
  GPIO_InitStruct.Pin = DFSDM1_DATIN2_Pin | DFSDM1_CKOUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF6_DFSDM1;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : QUADSPI_CLK_Pin QUADSPI_NCS_Pin OQUADSPI_BK1_IO0_Pin
     QUADSPI_BK1_IO1_Pin QUAD_SPI_BK1_IO2_Pin QUAD_SPI_BK1_IO3_Pin */
  GPIO_InitStruct.Pin = QUADSPI_CLK_Pin | QUADSPI_NCS_Pin |
                        OQUADSPI_BK1_IO0_Pin | QUADSPI_BK1_IO1_Pin |
                        QUAD_SPI_BK1_IO2_Pin | QUAD_SPI_BK1_IO3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : INTERNAL_UART3_TX_Pin INTERNAL_UART3_RX_Pin */
  GPIO_InitStruct.Pin = INTERNAL_UART3_TX_Pin | INTERNAL_UART3_RX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : LPS22HB_INT_DRDY_EXTI0_Pin PD11 ARD_D2_Pin
     HTS221_DRDY_EXTI15_Pin PMOD_IRQ_EXTI12_Pin */
  GPIO_InitStruct.Pin = LPS22HB_INT_DRDY_EXTI0_Pin | GPIO_PIN_11 | ARD_D2_Pin |
                        HTS221_DRDY_EXTI15_Pin | PMOD_IRQ_EXTI12_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : USB_OTG_FS_PWR_EN_Pin SPBTLE_RF_SPI3_CSN_Pin
   * PMOD_RESET_Pin STSAFE_A100_RESET_Pin */
  GPIO_InitStruct.Pin = USB_OTG_FS_PWR_EN_Pin | SPBTLE_RF_SPI3_CSN_Pin |
                        PMOD_RESET_Pin | STSAFE_A100_RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : VL53L0X_XSHUT_Pin LED3_WIFI__LED4_BLE_Pin */
  GPIO_InitStruct.Pin = VL53L0X_XSHUT_Pin | LED3_WIFI__LED4_BLE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : VL53L0X_GPIO1_EXTI7_Pin LSM3MDL_DRDY_EXTI8_Pin */
  GPIO_InitStruct.Pin = VL53L0X_GPIO1_EXTI7_Pin | LSM3MDL_DRDY_EXTI8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OTG_FS_VBUS_Pin */
  GPIO_InitStruct.Pin = USB_OTG_FS_VBUS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OTG_FS_VBUS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : USB_OTG_FS_ID_Pin USB_OTG_FS_DM_Pin USB_OTG_FS_DP_Pin
   */
  GPIO_InitStruct.Pin =
      USB_OTG_FS_ID_Pin | USB_OTG_FS_DM_Pin | USB_OTG_FS_DP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : INTERNAL_SPI3_SCK_Pin INTERNAL_SPI3_MISO_Pin
   * INTERNAL_SPI3_MOSI_Pin */
  GPIO_InitStruct.Pin =
      INTERNAL_SPI3_SCK_Pin | INTERNAL_SPI3_MISO_Pin | INTERNAL_SPI3_MOSI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PMOD_SPI2_SCK_Pin */
  GPIO_InitStruct.Pin = PMOD_SPI2_SCK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(PMOD_SPI2_SCK_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PMOD_UART2_CTS_Pin PMOD_UART2_RTS_Pin
   * PMOD_UART2_TX_Pin PMOD_UART2_RX_Pin */
  GPIO_InitStruct.Pin = PMOD_UART2_CTS_Pin | PMOD_UART2_RTS_Pin |
                        PMOD_UART2_TX_Pin | PMOD_UART2_RX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  if (GPIO_Pin == GPIO_PIN_11) {
    dataRdyIntReceived++;
  }
}

int _write(int fd, char *ptr, int len) {
  HAL_UART_Transmit(&huart1, (uint8_t *)ptr, len, HAL_MAX_DELAY);
  return len;
}

static void MEMS_Init(void) {
  LSM6DSL_IO_t io_ctx;
  uint8_t id;
  LSM6DSL_AxesRaw_t axes;
  /* Link I2C functions to the LSM6DSL driver */
  io_ctx.BusType = LSM6DSL_I2C_BUS;
  io_ctx.Address = LSM6DSL_I2C_ADD_L;
  io_ctx.Init = BSP_I2C2_Init;
  io_ctx.DeInit = BSP_I2C2_DeInit;
  io_ctx.ReadReg = BSP_I2C2_ReadReg;
  io_ctx.WriteReg = BSP_I2C2_WriteReg;
  io_ctx.GetTick = BSP_GetTick;
  LSM6DSL_RegisterBusIO(&MotionSensor, &io_ctx);
  /* Read the LSM6DSL WHO_AM_I register */
  LSM6DSL_ReadID(&MotionSensor, &id);
  if (id != LSM6DSL_ID) {
    Error_Handler();
  }
  /* Initialize the LSM6DSL sensor */
  LSM6DSL_Init(&MotionSensor);
  /* Configure the LSM6DSL accelerometer (ODR, scale and interrupt) */
  LSM6DSL_ACC_SetOutputDataRate(&MotionSensor, 26.0f); /* 26 Hz */
  LSM6DSL_ACC_SetFullScale(&MotionSensor, 4);
  LSM6DSL_GYRO_SetOutputDataRate(&MotionSensor, 26.0f); /* 26 Hz */
  LSM6DSL_GYRO_SetFullScale(&MotionSensor, 2000);
  /* [-4000mg; +4000mg] */
  LSM6DSL_ACC_Set_INT1_DRDY(&MotionSensor, ENABLE);
  LSM6DSL_GYRO_Set_INT1_DRDY(&MotionSensor, ENABLE);
  /* Enable DRDY */
  LSM6DSL_ACC_GetAxesRaw(&MotionSensor, &axes);
  LSM6DSL_GYRO_GetAxesRaw(&MotionSensor, &axes);
  /* Get axes */
  /* Start the LSM6DSL accelerometer */
  LSM6DSL_ACC_Enable(&MotionSensor);
  LSM6DSL_GYRO_Enable(&MotionSensor);
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1) {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line) {
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line
     number, ex: printf("Wrong parameters value: file %s on line %d\r\n", file,
     line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
