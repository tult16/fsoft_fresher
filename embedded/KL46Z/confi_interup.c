/* NHAY LED VOI f(n+1)=2fn VA DUA CODE LED BLINK VAO MAIN()*/
#include <stdio.h>
#include "MKL46Z4.h"
#define RedLED    29     // PTE pin 29
#define SW3          12     // PTC pin 12
uint32_t a,i,counter=0,togle=0;
uint32_t sw_press = 0;
uint32_t systick_on = 0u;

int main(void)
{
    // enable NVIC
    NVIC_EnableIRQ(PORTC_PORTD_IRQn);   // enables IRQ31

    // configuration gpio PORT C and PORT E,D
     SIM->SCGC5 |= SIM_SCGC5_PORTC(1) | SIM_SCGC5_PORTE(1) | SIM_SCGC5_PORTD(1); /* enable clock to Port C,D,E */

     PORTC->PCR[12]= PORT_PCR_MUX(1) | PORT_PCR_IRQC(10) | PORT_PCR_PE(1) | PORT_PCR_PS(1); /* make PTC3 pin as GPIO and enable pull-up resistor and chose rising clock */
     PORTD->PCR[5] = PORT_PCR_MUX(1);  //// Cconfiguration port D GPIO;
     //SIM->SCGC5 = SIM_SCGC5_PORTE(1)|| SIM_SCGC5_PORTD(1) ;   // enable clockgate

     uint32_t a;
     a = PORTE->PCR[29];
     a = (a & (~PORT_PCR_MUX_MASK))|PORT_PCR_MUX(1) ;   // DELETE BIT AND SET BIT
   	 PORTE->PCR[29] = a;								// configuration GPIO
     GPIOE->PDDR = (1U << 29);							// configuration is output, OUTPUT = 0 LED TURN ON RED
     GPIOE->PTOR = (1u<<29);							// TOGLE PIN 29: TURN OF LED RED
     ///
     GPIOD->PDDR = (1u << 5);
     GPIOD->PTOR = (1u<<5);
     //
     //if(sw_press == 1)

     	 while( 1)
     	 {
     		if(sw_press == 1)
     			{
     			(void)SysTick_Config(SystemCoreClock/counter);
     			sw_press = 0;
     				if(systick_on == 1)
     					{
     						GPIOE->PTOR = (1u<<29); //Change PTD5 to 1, turns LED OFF (Cathode connected to PTD5)
     						GPIOD->PTOR = (1u<<5);
     						systick_on = 0;
     					}

     			}
}
}
void PORTC_PORTD_IRQHandler(void)
{
	// clear flag interupt

	PORTC->PCR[12] |=PORT_PCR_ISF_MASK;			// CLEAR FLAG INTERRUPT
	//
    counter++;

    //
    sw_press = 1;
    ///


    //(void)SysTick_Config(SystemCoreClock/counter);

}

void SysTick_Handler(void)
{                               /* SysTick interrupt Handler.*/
  systick_on = 1;
}
