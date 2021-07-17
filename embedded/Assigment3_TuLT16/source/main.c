
/*******************************************************************************
 Assignment 3
 Author: TuLT16
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "initLed.h"
#include "systickConfig.h"

/*******************************************************************************
 * Global variable
 ******************************************************************************/
uint32_t g_Led1PulseWidth = 0;
uint32_t g_Led2PulseWidth = 0;
uint32_t g_MsTicksLed1 = 0;
uint32_t g_MsTicksLed2 = 0;

/*******************************************************************************
 * Codes
 ******************************************************************************/
int main (void)
{
    status_t status;
    uint32_t count = 0;
    
    Blink_led_setup(500, 1000);
    status = SysTicks_Config();
    if (STATUS_SUCCESS == status)
    {
        Start_blink_led();
        while (count < 100)
        {
            if (g_MsTicksLed1 == g_Led1PulseWidth)
            {
                ToggleLed(MCU_RED_LED_GPIO_REG, MCU_RED_LED_PIN_INDEX);
                g_MsTicksLed1 = 0;
                count++;
            }
            if (g_MsTicksLed2 == g_Led2PulseWidth)
            {
                ToggleLed(MCU_GREEN_LED_GPIO_REG, MCU_GREEN_LED_PIN_INDEX);
                g_MsTicksLed2 = 0;
            }
        }
        Stop_blink_led();
    }

    return 0;
}
