/*CHUONG TRINH THUC HIEN LED BLINK SAU 5 LAN BAM NUT*/
#include <stdio.h>
#include "MKL46Z4.h"
#define RedLED    29     // PTE pin 29
#define GreenLED 5       // PTD pin 5
#define SW1          3       // PTC pin 3
#define SW3          12     // PTC pin 12



uint32_t i=0u;
uint32_t counter=0u;

void PORTC_PORTD_IRQHandler(void);
int main(void){
    // enable NVIC
    NVIC_EnableIRQ(PORTC_PORTD_IRQn);   // enables IRQ31

    // configuration gpio PORT C and PORT E
     SIM->SCGC5 |= SIM_SCGC5_PORTC(1) | SIM_SCGC5_PORTE(1); /* enable clock to Port C,D */

     PORTC->PCR[12]= PORT_PCR_MUX(1) | PORT_PCR_IRQC(10) | PORT_PCR_PE(1) | PORT_PCR_PS(1); /* make PTC3 pin as GPIO and enable pull-up resistor and chose rising clock */

     //GPIOC->PDDR =(0u<<3); // set PTC3 input
    // configuration LED RED PTE 29
    // SIM->SCGC5 = SIM_SCGC5_PORTE(1) ;   // enable clockgate
     uint32_t a;
     a = PORTE->PCR[29];
     a = (a & (~PORT_PCR_MUX_MASK))|PORT_PCR_MUX(1) ;   // DELETE BIT AND SET BIT
   	 PORTE->PCR[29] = a;								// configuration GPIO
     GPIOE->PDDR = (1U << 29);							// configuration is output, OUTPUT = 0 LED TURN ON RED
     GPIOE->PTOR = (1u<<29);							// TOGLE PIN 29: TURN OF LED RED
    //uint32_t readPCR;
    //uint32_t IFS;


     while(1)
     {
    	 if(counter > 5)
    	 {
    	    GPIOE->PTOR = (1U << 29);	// TOGLE LED RED
    	    for(i = 0; i < 300000; i++){}
    	 }

     }
}
void PORTC_PORTD_IRQHandler(void){
	// clear flag interupt
	//uint32_t b = PORTC->PCR[3];
	//b =

	PORTC->PCR[12] |=PORT_PCR_ISF_MASK;			// CLEAR FLAG INTERRUPT
	//
	 counter ++;
	 if(counter <= 5)
	     	 {
	     	    GPIOE->PTOR = (1U << 29);	// TOGLE LED RED
	     	 }

}
