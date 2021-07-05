#include "initLed.h"

/* Function init led */
void initLed()
{
    /* Enable clock gate port E, port D */
    SIM->SCGC5 = SIM_SCGC5_PORTE(1) | SIM_SCGC5_PORTD(1);
    /* Set pin led red and green as GPIO */
    PORTE->PCR[29] = PORT_PCR_MUX(1);
    PORTD->PCR[5] = PORT_PCR_MUX(1);
    /* Set pin led red and green as output */
    GPIOE->PDDR |= (1U << 29);
    GPIOD->PDDR |= (1U << 5);
}

