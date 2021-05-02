// #include "stm32f4xx_hal.h"
// #include "stm32f446xx.h"

// #define USER_Btn_Pin GPIO_PIN_13
// #define USER_Btn_GPIO_Port GPIOC
// #define MCO_Pin GPIO_PIN_0
// #define MCO_GPIO_Port GPIOH
// #define LD1_Pin GPIO_PIN_0
// #define LD1_GPIO_Port GPIOB
// #define LD3_Pin GPIO_PIN_14
// #define LD3_GPIO_Port GPIOB
// #define STLK_RX_Pin GPIO_PIN_8
// #define STLK_RX_GPIO_Port GPIOD
// #define STLK_TX_Pin GPIO_PIN_9
// #define STLK_TX_GPIO_Port GPIOD
// #define USB_PowerSwitchOn_Pin GPIO_PIN_6
// #define USB_PowerSwitchOn_GPIO_Port GPIOG
// #define USB_OverCurrent_Pin GPIO_PIN_7
// #define USB_OverCurrent_GPIO_Port GPIOG
// #define USB_SOF_Pin GPIO_PIN_8
// #define USB_SOF_GPIO_Port GPIOA
// #define USB_VBUS_Pin GPIO_PIN_9
// #define USB_VBUS_GPIO_Port GPIOA
// #define USB_ID_Pin GPIO_PIN_10
// #define USB_ID_GPIO_Port GPIOA
// #define USB_DM_Pin GPIO_PIN_11
// #define USB_DM_GPIO_Port GPIOA
// #define USB_DP_Pin GPIO_PIN_12
// #define USB_DP_GPIO_Port GPIOA
// #define TMS_Pin GPIO_PIN_13
// #define TMS_GPIO_Port GPIOA
// #define TCK_Pin GPIO_PIN_14
// #define TCK_GPIO_Port GPIOA
// #define LD2_Pin GPIO_PIN_7
// #define LD2_GPIO_Port GPIOB

// TIM_HandleTypeDef htim6;

// void Error_Handler(void);
// void SystemClock_Config(void);

// void HAL_MspInit(void)
// {
//   /* USER CODE BEGIN MspInit 0 */

//   /* USER CODE END MspInit 0 */

//   __HAL_RCC_SYSCFG_CLK_ENABLE();
//   __HAL_RCC_PWR_CLK_ENABLE();

//   /* System interrupt init*/
//   /* PendSV_IRQn interrupt configuration */
//   HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);

//   /* USER CODE BEGIN MspInit 1 */

//   /* USER CODE END MspInit 1 */
// }

// void HAL_SuspendTick(void)
// {
//   /* Disable TIM6 update Interrupt */
//   __HAL_TIM_DISABLE_IT(&htim6, TIM_IT_UPDATE);
// }

// /**
//   * @brief  Resume Tick increment.
//   * @note   Enable the tick increment by Enabling TIM6 update interrupt.
//   * @param  None
//   * @retval None
//   */
// void HAL_ResumeTick(void)
// {
//   /* Enable TIM6 Update interrupt */
//   __HAL_TIM_ENABLE_IT(&htim6, TIM_IT_UPDATE);
// }

// void SysTick_Handler (void) {
//   /* Clear overflow flag */
//   SysTick->CTRL;

//   if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) {
//     /* Call tick handler */
//     xTaskIncrementTick();
//   }
// }

// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
// {
//   /* USER CODE BEGIN Callback 0 */

//   /* USER CODE END Callback 0 */
//   if (htim->Instance == TIM6) {
//     HAL_IncTick();
//   }
//   /* USER CODE BEGIN Callback 1 */

//   /* USER CODE END Callback 1 */
// }


// HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
// {
//   RCC_ClkInitTypeDef    clkconfig;
//   uint32_t              uwTimclock = 0;
//   uint32_t              uwPrescalerValue = 0;
//   uint32_t              pFLatency;
//   /*Configure the TIM6 IRQ priority */
//   HAL_NVIC_SetPriority(TIM6_DAC_IRQn, TickPriority ,0);

//   /* Enable the TIM6 global Interrupt */
//   HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
//   /* Enable TIM6 clock */
//   __HAL_RCC_TIM6_CLK_ENABLE();

//   /* Get clock configuration */
//   HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);

//   /* Compute TIM6 clock */
//   uwTimclock = 2*HAL_RCC_GetPCLK1Freq();
//   /* Compute the prescaler value to have TIM6 counter clock equal to 1MHz */
//   uwPrescalerValue = (uint32_t) ((uwTimclock / 1000000U) - 1U);

//   /* Initialize TIM6 */
//   htim6.Instance = TIM6;

//   /* Initialize TIMx peripheral as follow:
//   + Period = [(TIM6CLK/1000) - 1]. to have a (1/1000) s time base.
//   + Prescaler = (uwTimclock/1000000 - 1) to have a 1MHz counter clock.
//   + ClockDivision = 0
//   + Counter direction = Up
//   */
//   htim6.Init.Period = (1000000U / 1000U) - 1U;
//   htim6.Init.Prescaler = uwPrescalerValue;
//   htim6.Init.ClockDivision = 0;
//   htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
//   if(HAL_TIM_Base_Init(&htim6) == HAL_OK)
//   {
//     /* Start the TIM time Base generation in interrupt mode */
//     return HAL_TIM_Base_Start_IT(&htim6);
//   }

//   /* Return function status */
//   return HAL_ERROR;
// }

// void Error_Handler(void)
// {
//   /* USER CODE BEGIN Error_Handler_Debug */
//   /* User can add his own implementation to report the HAL error return state */
//   __disable_irq();
//   while (1)
//   {
//   }
//   /* USER CODE END Error_Handler_Debug */
// }

// void SystemClock_Config(void)
// {
//   RCC_OscInitTypeDef RCC_OscInitStruct = {0};
//   RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
//   RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

//   /** Configure the main internal regulator output voltage
//   */
//   __HAL_RCC_PWR_CLK_ENABLE();
//   __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
//   /** Initializes the RCC Oscillators according to the specified parameters
//   * in the RCC_OscInitTypeDef structure.
//   */
//   RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
//   RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
//   RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
//   RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
//   RCC_OscInitStruct.PLL.PLLM = 4;
//   RCC_OscInitStruct.PLL.PLLN = 168;
//   RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
//   RCC_OscInitStruct.PLL.PLLQ = 7;
//   RCC_OscInitStruct.PLL.PLLR = 2;
//   if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
//   {
//     Error_Handler();
//   }
//   /** Initializes the CPU, AHB and APB buses clocks
//   */
//   RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
//                               |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
//   RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
//   RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
//   RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
//   RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

//   if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
//   {
//     Error_Handler();
//   }
//   PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CLK48;
//   PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48CLKSOURCE_PLLQ;
//   if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
//   {
//     Error_Handler();
//   }
// }

// void HAL_UART_MspInit(UART_HandleTypeDef* huart)
// {

// }

// /**
// * @brief UART MSP De-Initialization
// * This function freeze the hardware resources used in this example
// * @param huart: UART handle pointer
// * @retval None
// */
// void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
// {

// }

// /**
// * @brief PCD MSP Initialization
// * This function configures the hardware resources used in this example
// * @param hpcd: PCD handle pointer
// * @retval None
// */
// void HAL_PCD_MspInit(PCD_HandleTypeDef* hpcd)
// {
//   GPIO_InitTypeDef GPIO_InitStruct = {0};
//   if(hpcd->Instance==USB_OTG_FS)
//   {
//   /* USER CODE BEGIN USB_OTG_FS_MspInit 0 */

//   /* USER CODE END USB_OTG_FS_MspInit 0 */

//     __HAL_RCC_GPIOA_CLK_ENABLE();
//     /**USB_OTG_FS GPIO Configuration
//     PA8     ------> USB_OTG_FS_SOF
//     PA9     ------> USB_OTG_FS_VBUS
//     PA10     ------> USB_OTG_FS_ID
//     PA11     ------> USB_OTG_FS_DM
//     PA12     ------> USB_OTG_FS_DP
//     */
//     GPIO_InitStruct.Pin = USB_SOF_Pin|USB_ID_Pin|USB_DM_Pin|USB_DP_Pin;
//     GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//     GPIO_InitStruct.Pull = GPIO_NOPULL;
//     GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//     GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
//     HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

//     GPIO_InitStruct.Pin = USB_VBUS_Pin;
//     GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//     GPIO_InitStruct.Pull = GPIO_NOPULL;
//     HAL_GPIO_Init(USB_VBUS_GPIO_Port, &GPIO_InitStruct);

//     /* Peripheral clock enable */
//     __HAL_RCC_USB_OTG_FS_CLK_ENABLE();
//   /* USER CODE BEGIN USB_OTG_FS_MspInit 1 */

//   /* USER CODE END USB_OTG_FS_MspInit 1 */
//   }

// }

// /**
// * @brief PCD MSP De-Initialization
// * This function freeze the hardware resources used in this example
// * @param hpcd: PCD handle pointer
// * @retval None
// */
// void HAL_PCD_MspDeInit(PCD_HandleTypeDef* hpcd)
// {
//   if(hpcd->Instance==USB_OTG_FS)
//   {
//   /* USER CODE BEGIN USB_OTG_FS_MspDeInit 0 */

//   /* USER CODE END USB_OTG_FS_MspDeInit 0 */
//     /* Peripheral clock disable */
//     __HAL_RCC_USB_OTG_FS_CLK_DISABLE();

//     /**USB_OTG_FS GPIO Configuration
//     PA8     ------> USB_OTG_FS_SOF
//     PA9     ------> USB_OTG_FS_VBUS
//     PA10     ------> USB_OTG_FS_ID
//     PA11     ------> USB_OTG_FS_DM
//     PA12     ------> USB_OTG_FS_DP
//     */
//     HAL_GPIO_DeInit(GPIOA, USB_SOF_Pin|USB_VBUS_Pin|USB_ID_Pin|USB_DM_Pin
//                           |USB_DP_Pin);

//   /* USER CODE BEGIN USB_OTG_FS_MspDeInit 1 */

//   /* USER CODE END USB_OTG_FS_MspDeInit 1 */
//   }
// }

// /**
//   * @brief This function handles TIM6 global interrupt and DAC1, DAC2 underrun error interrupts.
//   */
// void TIM6_DAC_IRQHandler(void)
// {
//   /* USER CODE BEGIN TIM6_DAC_IRQn 0 */

//   /* USER CODE END TIM6_DAC_IRQn 0 */
//   HAL_TIM_IRQHandler(&htim6);
//   /* USER CODE BEGIN TIM6_DAC_IRQn 1 */

//   /* USER CODE END TIM6_DAC_IRQn 1 */
// }