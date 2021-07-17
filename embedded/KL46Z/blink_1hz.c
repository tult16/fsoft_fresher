/* NHAY LED SU DUNG SYSTIC VOI T=0,5s */
#include <stdio.h>
#include "MKL46Z4.h"

uint32_t msTicks = 0;                                       /* Variable to store millisecond ticks */


void SysTick_Handler(void)  {                               /* SysTick interrupt Handler.*/
  msTicks++;
  GPIOE->PTOR = (1u<<29); //Change PTD5 to 1, turns LED OFF (Cathode connected to PTD5)
  GPIOD->PTOR = (1u<<5);                                                  //See startup file startup_LPC17xx.s for SysTick vector */
}


int main (void)  {

	SIM->SCGC5 = SIM_SCGC5_PORTE(1) | SIM_SCGC5_PORTD(1);  // BIT 13 DUOC CAU HINH, CAC BIT KHAC KHONG THAY DOI.
	PORTE->PCR[29] = PORT_PCR_MUX(1);
	//SIM->SCGC5 = SIM_SCGC5_PORTD(1);
	PORTD->PCR[5] = PORT_PCR_MUX(1);

	GPIOE->PDDR |= (1U << 29);
	GPIOD->PDDR |= (1U << 5);

	uint32_t returnCode;

    returnCode = SysTick_Config(SystemCoreClock / 2);      /* Configure SysTick to generate an interrupt every millisecond */

        if (returnCode != 0)
            {                                   /* Check return code for errors */
    // Error Handling
            }

  while(1);
}
