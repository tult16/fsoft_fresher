/*******************************************************************************
 * Assignment 4
 * Author : TuLT16
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "MKL46Z4.h"
#include "initLed.h"
#include "initPIT.h"

/*******************************************************************************
 * Defines
 ******************************************************************************/
#define LED_RED_ON              GPIOE->PCOR |= (1 << 29)
#define LED_RED_OFF             GPIOE->PSOR |= (1 << 29)
#define LED_GREEN_ON            GPIOD->PCOR |= (1 << 5)
#define LED_GREEN_OFF           GPIOD->PSOR |= (1 << 5)

/*******************************************************************************
 * Variables
 ******************************************************************************/
unsigned char led1_on  = 2 ;
unsigned char led1_off  = 1;
unsigned char led2_on  = 1;
unsigned char led2_off  = 3;
volatile uint32_t g_led1count = 0;
volatile uint32_t g_led2count = 0;

/*******************************************************************************
 * Code
 ******************************************************************************/
int main(void)
{
    /* Function init led */
    initLed();
    /* Function init PIT */
    init_PIT();
    LED_RED_ON;
    LED_GREEN_ON;

    while(1)
    {
        if (g_led1count == led1_on)
        {
            LED_RED_OFF;
        }
        if (g_led1count == (led1_on + led1_off))
        {
            LED_RED_ON;
            g_led1count = 0;
        }
        if (g_led2count == led2_on)
        {
            LED_GREEN_OFF;
        }
        if (g_led2count == (led2_on + led2_off))
        {
            LED_GREEN_ON;
            g_led2count = 0;
        }
    }

    return 0;
}

