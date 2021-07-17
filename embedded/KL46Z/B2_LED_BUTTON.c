//2. PRESS SWITCHES TO TURN LED GREEN

/**
 * @file    MKL46Z256xxx4_tu_button_led.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "MKL46Z4.h"
int main(void) {

    SIM->SCGC5 |= SIM_SCGC5_PORTD(1); /* enable clock to Port D */

    PORTD->PCR[5] = PORT_PCR_MUX(1); /* make PTD5 pin as GPIO */

    PTD->PDDR |= (1<<5); /* make PTD5 as output pin */

    SIM->SCGC5 |= SIM_SCGC5_PORTC(1); /* enable clock to Port C */

    PORTC->PCR[3]= PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;; /* make PTC3 pin as GPIO and enable pull-up resistor */

    FPTC->PDDR &= ~(1<<3); /* make PTA1 as input pin */

while (1) {

    if (PTC->PDIR & (1<<3)) /* check to see if SW1 is pressed */

        PTD->PSOR |= (1<<5); /* if not, turn off green LED */

    else

        PTD->PCOR |= (1<<5); /* turn on green LED */

}
return 0;
}

