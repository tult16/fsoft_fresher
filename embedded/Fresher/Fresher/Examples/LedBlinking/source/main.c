#include "MKL46Z4.h"

#define RED_LED_ON      GPIOD->PCOR |= (1 << 5)
#define RED_LED_OFF     GPIOD->PSOR |= (1 << 5)
#define GREEN_LED_ON    GPIOE->PCOR |= (1 << 29)
#define GREEN_LED_OFF   GPIOE->PSOR |= (1 << 29)

#define DELAY_COUNT     1000000UL

void initLed();
void delay();

void main()
{
    initLed();
    
    while (1)
    {
        /* Set PTD5 and PTE29 */
        RED_LED_ON;
        GREEN_LED_ON;
        /* Delay */
        delay();
        /* Clear PTD5 and PTE29 */
        RED_LED_OFF;
        GREEN_LED_OFF;
        /* Delay */
        delay();
    }
}

void initLed()
{
    /* Enable clock for PORTD, PORTE */
    SIM->SCGC5 |= (1 << 12);    /* Set bit 12 */
    SIM->SCGC5 |= (1 << 13);    /* Set bit 13 */
    
    /* Configure multiplex of PTD5 and PTE29 as GPIO */
    PORTD->PCR[5] |= PORT_PCR_MUX(1);
    PORTE->PCR[29] |= PORT_PCR_MUX(1);
    
    /* Configure PTD5 and PTE29 as output */
    GPIOD->PDDR |= (1 << 5);
    GPIOE->PDDR |= (1 << 29);
    
    /* Clear PTD5 and PTE29 */
    RED_LED_ON;
    GREEN_LED_ON;
}

void delay()
{
    unsigned long i;
    
    for (i = 0; i < DELAY_COUNT; i++)
    {
        __asm("nop");
    }
}