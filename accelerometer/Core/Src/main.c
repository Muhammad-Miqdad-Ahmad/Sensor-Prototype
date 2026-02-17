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
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
LSM6DSL_Object_t MotionSensor;
volatile uint32_t dataRdyIntReceived;

/* USER CODE BEGIN PV */
/* existing vars ... */

#define WINDOW_SIZE 40
#define NUM_FEATURES 6
#define MODEL_INPUT_SIZE (WINDOW_SIZE * NUM_FEATURES) // 240

/* Put the real numbers you printed from Python here */
// static const float scaler_mean[NUM_FEATURES] = {/* e.g. -0.01, 0.02, ... */};
// static const float scaler_scale[NUM_FEATURES] = {/* e.g. 0.98, 1.02, ... */};
static const float scaler_mean[NUM_FEATURES] = {
    -0.12441810504811437, -0.3559780137995743, -0.45115355966812687,
    -0.2609845578559185,  1.1738487249314078,  0.30543802135980275};
static const float scaler_scale[NUM_FEATURES] = {
    1.707759339926897,  1.8599862252629156, 2.7341685924809713,
    0.8088201806264358, 1.9792116598123928, 3.675394912367162};

/* Quant params (replace with analyzer-generated values if different) */
static const float MODEL_INPUT_SCALE = 0.119718373f;
static const int MODEL_INPUT_ZP = 25; /* zero point */
static const float MODEL_OUTPUT_SCALE = 0.00390625f;
static const int MODEL_OUTPUT_ZP = -128;

/* sliding buffer for raw samples (int16 or float) */
static int32_t sample_buffer[WINDOW_SIZE]
                            [NUM_FEATURES]; // raw readings copy; use int32 to
                                            // hold raw LSM6DSL values
static uint16_t sample_count = 0;

/* model input in quantized int8 form */
static int8_t model_input[MODEL_INPUT_SIZE];

/* model output (int8, 5 classes) */
static int8_t model_output[5];

/* Cube.AI handle (declared here) */
static ai_handle model = AI_HANDLE_NULL;

/* activation buffer: Cube.AI generated macro defines size, but show a fallback
 */
#ifndef AI_HARSH_DETECTION_PROTOTYPE_DATA_ACTIVATIONS_SIZE
#define AI_HARSH_DETECTION_PROTOTYPE_DATA_ACTIVATIONS_SIZE (8192)
#endif
static uint8_t activations[AI_HARSH_DETECTION_PROTOTYPE_DATA_ACTIVATIONS_SIZE];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
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
  /* USER CODE BEGIN 2 */

  dataRdyIntReceived = 0;
  // For the inbuilt accelerometer
  MEMS_Init();

  // The lcd library init
  ssd1306_Init();
  /* USER CODE BEGIN 2 */
  /* after ssd1306_Init() etc. */

  ai_error err;
  ai_network_params params = {
      .params = AI_HARSH_DETECTION_PROTOTYPE_DATA_WEIGHTS(0),
      .activations =
          AI_HARSH_DETECTION_PROTOTYPE_DATA_ACTIVATIONS(activations)};

  /* create the network */
  err = ai_harsh_detection_prototype_create(
      &model, AI_HARSH_DETECTION_PROTOTYPE_DATA_CONFIG);
  if (err.type != AI_ERROR_NONE) {
    printf("AI create error: %d\n", err.type);
    Error_Handler();
  }

  /* initialize the network */
  if (!ai_harsh_detection_prototype_init(model, &params)) {
    printf("AI init failed\n");
    Error_Handler();
  }

  /* USER CODE END 2 */

  // Clearing the screen
  ssd1306_Fill(Black);
  // actually applies the changes to the screen
  ssd1306_UpdateScreen();

  ssd1306_SetCursor(0, 0);
  ssd1306_WriteString("HELLO", Font_11x18, White);

  ssd1306_SetCursor(0, 30);
  ssd1306_WriteString("LED working now", Font_7x10, White);

  ssd1306_UpdateScreen();
  HAL_Delay(5000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  /* USER CODE BEGIN WHILE */
  while (1) {
    if (dataRdyIntReceived != 0) {
      dataRdyIntReceived = 0;

      /* read accel & gyro (if radar or gyro not configured, set zeros) */
      LSM6DSL_Axes_t acc_axes;
      LSM6DSL_Axes_t gyro_axes;
      LSM6DSL_ACC_GetAxes(&MotionSensor, &acc_axes);
      // if you have gyro API call it: LSM6DSL_GYRO_GetAxes(&MotionSensor,
      // &gyro_axes); if not, zero the gyro values:
      gyro_axes.x = 0;
      gyro_axes.y = 0;
      gyro_axes.z = 0;

      /* Append new sample to circular buffer */
      uint16_t idx = sample_count % WINDOW_SIZE;
      sample_buffer[idx][0] = acc_axes.x;
      sample_buffer[idx][1] = acc_axes.y;
      sample_buffer[idx][2] = acc_axes.z;
      sample_buffer[idx][3] = gyro_axes.x;
      sample_buffer[idx][4] = gyro_axes.y;
      sample_buffer[idx][5] = gyro_axes.z;

      sample_count++;

      /* If we have a full window, prepare input and run model */
      if (sample_count >= WINDOW_SIZE) {
        /* Important: your model expects data in the exact order & preprocessing
           used during training. This code assumes StandardScaler was trained on
           the same raw units (acc/gyro). Apply the scaler: (x - mean) / scale
        */

        /* Prepare quantized input: model_input[] length = 240 (40*6) */
        for (int i = 0; i < WINDOW_SIZE; ++i) {
          /* sliding window order: oldest->newest
             compute the right index into circular buffer */
          int buf_idx = (sample_count - WINDOW_SIZE + i) % WINDOW_SIZE;
          if (buf_idx < 0)
            buf_idx += WINDOW_SIZE;

          for (int ch = 0; ch < NUM_FEATURES; ++ch) {
            float raw = (float)sample_buffer[buf_idx][ch];
            /* apply StandardScaler used in training */
            float norm = (raw - scaler_mean[ch]) / scaler_scale[ch];

            /* quantize to int8: q = round(norm / MODEL_INPUT_SCALE) +
             * MODEL_INPUT_ZP */
            int32_t q =
                (int32_t)lrintf(norm / MODEL_INPUT_SCALE) + MODEL_INPUT_ZP;
            if (q > 127)
              q = 127;
            if (q < -128)
              q = -128;
            model_input[i * NUM_FEATURES + ch] = (int8_t)q;
          }
        }

        /* Now call the generated run function. Use the exact signature Cube.AI
           produced. Most generated examples use ai_buffer and
           ai_harsh_detection_prototype_run(...). A very simple wrapper often
           exists; here's a generic call:
        */

        /* build ai_buffer structures - use the generated helpers if present */
        /* This snippet uses the raw run API which many Cube.AI examples expose:
           int ai_harsh_detection_prototype_run(ai_handle network, const
           ai_buffer* input, ai_buffer* output)
        */
        /* If your project provides helpers, follow that instead. */

        /* Prepare buffers using the generated macros if available: */
#ifdef AI_HARSH_DETECTION_PROTOTYPE_IN_1_SIZE
        /* Example using generated buffer macros if present (preferred) */
        // ai_buffer ai_input[AI_HARSH_DETECTION_PROTOTYPE_IN_NUM] =
        //     AI_HARSH_DETECTION_PROTOTYPE_IN;
        // ai_buffer ai_output[AI_HARSH_DETECTION_PROTOTYPE_OUT_NUM] =
        //     AI_HARSH_DETECTION_PROTOTYPE_OUT;
        // /* assign data pointers */
        // ai_input[0].data = AI_HANDLE_PTR(model_input);
        // ai_output[0].data = AI_HANDLE_PTR(model_output);
        ai_buffer *ai_input =
            ai_harsh_detection_prototype_inputs_get(model, NULL);
        ai_buffer *ai_output =
            ai_harsh_detection_prototype_outputs_get(model, NULL);

        if (ai_input == NULL || ai_output == NULL) {
          printf("Failed to get ai buffers from generated API\n");
          Error_Handler();
        }

        /* override data pointers to point to your quantized buffers */
        ai_input[0].data = AI_HANDLE_PTR(model_input);
        ai_output[0].data = AI_HANDLE_PTR(model_output);

        if (ai_harsh_detection_prototype_run(model, &ai_input[0],
                                             &ai_output[0]) != 1) {
          printf("AI run failed\n");
        }
#else
        /* Minimal fallback: many generated examples provide a simple run
         * wrapper */
        int res = ai_harsh_detection_prototype_run(
            model,
            (const void *)
                model_input,       /* input ptr - adapt if signature differs */
            (void *)model_output); /* output ptr  */
        /* If your generated API differs, adapt accordingly. */
#endif

        /* Convert quantized outputs to float scores and find argmax */
        // float scores[5];
        int best_idx = 0;
        float best_score = -1e9f;
        for (int k = 0; k < 5; ++k) {
          int8_t q = model_output[k];
          float val = ((float)((int)q - MODEL_OUTPUT_ZP)) * MODEL_OUTPUT_SCALE;
          // scores[k] = val;
          if (val > best_score) {
            best_score = val;
            best_idx = k;
          }
        }

        /* Display predicted class & confidence on LCD */
        char buf[32];
        const char *labels[5] = {"Normal", "Brake", "Accel", "Right", "Left"};
        sprintf(buf, "%s", labels[best_idx]);
        ssd1306_Fill(Black);
        ssd1306_SetCursor(0, 0);
        ssd1306_WriteString(buf, Font_11x18, White);
        sprintf(buf, "score: %.2f", best_score);
        ssd1306_SetCursor(0, 30);
        ssd1306_WriteString(buf, Font_7x10, White);
        ssd1306_UpdateScreen();

        /* Optionally shift the buffer by step (if overlapping windows). In your
           training you used step=10. To mimic training sliding-window behavior,
           you can retain last 30 samples and continue collecting. Easiest:
           decrement sample_count by STEP so next inference starts after a
           stride.
        */
        sample_count -=
            10; // STEP_SIZE = 10; ensures overlapping windows like training
      }

      /* small debounce/delay or not depending on sampling ODR */
      HAL_Delay(1000);
    }
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
  /* [-4000mg; +4000mg] */
  LSM6DSL_ACC_Set_INT1_DRDY(&MotionSensor, ENABLE);
  /* Enable DRDY */
  LSM6DSL_ACC_GetAxesRaw(&MotionSensor, &axes);
  /* Get axes */
  /* Start the LSM6DSL accelerometer */
  LSM6DSL_ACC_Enable(&MotionSensor);
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
