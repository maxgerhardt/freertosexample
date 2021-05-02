#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

#include "stm32f4xx_hal.h"
#include "stm32f446xx.h"

static void BlinkBlueLed( void * pvParameters )
{
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for( ;; )
    {
        GPIOB->ODR ^= GPIO_PIN_7;
        
        // HAL_Delay(10000);
        // Wait for the next cycle.
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        // vTaskDelayUntil( &xLastWakeTime, 1000 );
    }
}

static void BlinkRedLed( void * pvParameters )
{
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for( ;; )
    {
        GPIOB->ODR ^= GPIO_PIN_14;
        // Wait for the next cycle.
        vTaskDelayUntil( &xLastWakeTime, 1000 );
    }
}

int main()
{
    HAL_Init();

    __GPIOB_CLK_ENABLE();
    
    GPIO_InitTypeDef gpio;
    gpio.Pin = GPIO_PIN_0 | GPIO_PIN_7 | GPIO_PIN_14;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOB, &gpio);

    xTaskCreate( 
        BlinkRedLed,
        "BlinkRed",
        200,
        NULL,
        1,
        NULL );

    xTaskCreate( 
        BlinkBlueLed,
        "BlinkBlue",
        200,
        NULL,
        1,
        NULL );

     // Start the real time scheduler.
     xPortStartScheduler();

    while(1)
    {
    }
}

void SysTick_Handler(void)
{
    HAL_IncTick();
    HAL_SYSTICK_IRQHandler();

    xPortSysTickHandler();
}

void NMI_Handler(void)
{
  while (1)
  {
  }
}

void HardFault_Handler(void)
{
  while (1)
  {
  }
}

void MemManage_Handler(void)
{
  while (1)
  {
  }
}

void BusFault_Handler(void)
{
  while (1)
  {
  }
}

void UsageFault_Handler(void)
{
  while (1)
  {
  }
}

void DebugMon_Handler(void)
{
}