//1. LED BLINK KHONG DUNG NGAT TIMER
#include <stdio.h>
#include "MKL46Z4.h"
void BlinkLED2(void);
int main(){
printf("hello world");
SIM->SCGC5 = SIM_SCGC5_PORTE(1) | SIM_SCGC5_PORTD(1);  // BIT 13 DUOC CAU HINH, CAC BIT KHAC KHONG THAY DOI.
PORTE->PCR[29] = PORT_PCR_MUX(1);
//SIM->SCGC5 = SIM_SCGC5_PORTD(1);
PORTD->PCR[5] = PORT_PCR_MUX(1);

GPIOE->PDDR |= (1U << 29);
GPIOD->PDDR |= (1U << 5);
 while(1)
 {
 BlinkLED2();
}
 return 0;

}
void BlinkLED2(void){//This method turns the LED off, then back on using PDOR
    //Note the use of |= and &=.  This allows you to change the 5th bit of PDOR without disturbing the other bits.  The other methods do not require this as setting PSOR/PCOR/PTOR = 0 does not change the output.
    uint32_t i = 0; //Create a loop variable

    GPIOE->PTOR = (1u<<29); //Change PTD5 to 1, turns LED OFF (Cathode connected to PTD5)
    GPIOD->PTOR = (1u<<5); //Change PTD5 to 0, turns LED ON.  This line is a bit weird.  First it takes 1u<<5 and typecasts ( http://en.wikipedia.org/wiki/Type_conversion ) it to a 32 bit value.  It then takes the inverse of it, so all bits are 1 except bit 5.  It then logical ands it with the current PDOR, which will retain all values except bit 5 which will be changed to 0.
    for(i=0; i < 300000; i++){}; //Burn some time

   // for(i=0; i < 300000; i++){}; //Burn some time
}
