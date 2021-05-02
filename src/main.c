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
		(void) xLastWakeTime; //suprress unused paramter warning
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
     vTaskStartScheduler();

    while(1)
    {
    }
}

extern void xPortSysTickHandler(void);

void SysTick_Handler(void)
{
    HAL_IncTick();
    HAL_SYSTICK_IRQHandler();
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
    {
        xPortSysTickHandler();
    }
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

/* functions that need to be implemented by the application because static allocation and timers are actived. */
/* copied from FreeRTOS documentation https://www.freertos.org/a00110.html#configSUPPORT_STATIC_ALLOCATION */

/* configSUPPORT_STATIC_ALLOCATION is set to 1, so the application must provide an
implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
used by the Idle task. */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize )
{
/* If the buffers to be provided to the Idle task are declared inside this
function then they must be declared static - otherwise they will be allocated on
the stack and so not exists after this function exits. */
static StaticTask_t xIdleTaskTCB;
static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
    state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

/* configSUPPORT_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
application must provide an implementation of vApplicationGetTimerTaskMemory()
to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize )
{
/* If the buffers to be provided to the Timer task are declared inside this
function then they must be declared static - otherwise they will be allocated on
the stack and so not exists after this function exits. */
static StaticTask_t xTimerTaskTCB;
static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

    /* Pass out a pointer to the StaticTask_t structure in which the Timer
    task's state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task's stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configTIMER_TASK_STACK_DEPTH is specified in words, not bytes. */
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
