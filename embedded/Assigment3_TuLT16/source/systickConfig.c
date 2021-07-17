#include "systickConfig.h"

/* Function sysTick interrupt handler.*/
void SysTick_Handler(void)
{
    g_MsTicksLed1++;
    g_MsTicksLed2++;
}

/* Function systicks configration */
status_t SysTicks_Config(void)
{
    uint32_t ticks =  SystemCoreClock/1000;
    status_t status = STATUS_SUCCESS;

    if((ticks - 1UL) > MCU_SysTick_LOAD_RELOAD_Msk)
    {
        status = STATUS_INVALID_PARAM;
    }
    else
    {
        /* set reload register */
        MCU_SysTick->LOAD  = (uint32_t)(ticks - 1UL);
        /* Load the SysTick Counter Value */
        MCU_SysTick->VAL   = 0UL;
        /* Enable SysTick IRQ and SysTick Timer */
        MCU_SysTick->CTRL  = MCU_SysTick_CTRL_CLKSOURCE_Msk |
                             MCU_SysTick_CTRL_TICKINT_Msk   |
                             (~MCU_SysTick_CTRL_ENABLE_Msk);
        /* set Priority for Systick Interrupt */
        NVIC_SetPriority(SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL);
    }

    return status;
}
