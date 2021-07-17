#include "initLed.h"

/* Function blink led setup */
void Blink_led_setup(uint32_t time1, uint32_t time2)
{
    /* Enable clock gate port E, port D */
    MCU_SIM->SCGC5 = MCU_SIM_SCGC5_PORTE(1) | MCU_SIM_SCGC5_PORTD(1);

    /* Set pin led red and green as GPIO */
    MCU_RED_LED_PORT_REG->PCR[MCU_RED_LED_PIN_INDEX] = MCU_PORT_PCR_MUX(1);
    MCU_GREEN_LED_PORT_REG->PCR[MCU_GREEN_LED_PIN_INDEX] = MCU_PORT_PCR_MUX(1);

    /* Set pin led red and green as output */
    MCU_RED_LED_GPIO_REG->PDDR |= (1U << MCU_RED_LED_PIN_INDEX);
    MCU_GREEN_LED_GPIO_REG->PDDR |= (1U << MCU_GREEN_LED_PIN_INDEX);

    g_Led1PulseWidth = time1;
    g_Led2PulseWidth = time2;

}

/* Function toggle pin Logic level */
void ToggleLed(MCU_GPIO_Type * base, uint8_t pinIndex)
{
    base->PTOR = (uint32_t)(1 << pinIndex);
}

/* Function start blink led */
void Start_blink_led(void)
{
    MCU_SysTick->CTRL = MCU_SysTick->CTRL & (~MCU_SysTick_CTRL_ENABLE_Msk) | MCU_SysTick_CTRL_ENABLE_Msk;
}

/* Function stop blink led */
void Stop_blink_led(void)
{
    MCU_SysTick->CTRL = MCU_SysTick->CTRL & (~MCU_SysTick_CTRL_ENABLE_Msk);
}

