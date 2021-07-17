/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "initSwitch.h"

/*******************************************************************************
 * Codes
 ******************************************************************************/

/* Function init switch 2 as GPIO intput */
void initSwitch(void)
{
    /* Enable clock gate port C */
    SIM->SCGC5=(SIM->SCGC5 & (~SIM_SCGC5_PORTC_MASK)) |SIM_SCGC5_PORTC(1) ;
    /* Set PTC12(sw2) as GPIO */
    PORTC->PCR[12] = (PORTC->PCR[12] & (~PORT_PCR_MUX_MASK)) |PORT_PCR_MUX(1) |PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    /* Set PTC12 as input */
    PTC->PDDR &= (~(1 << 12));
}
