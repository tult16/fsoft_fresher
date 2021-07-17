
// #include "MKL46Z4.h"
// //UART0,PTA1=RX and PTA1=TX
// void UART_Init(void){
//     SIM->SOPT2=(1u<<26);//SIM->SOPT2_UART0SRC(1);Clock to UART0 MCGFLLCLK 20.97152MHz as MCG_C4=0x00 low range 20Mhz
//     //SIM->SOPT5=0x00;
//     //open-drain mode disabled(Clear bit 16) plus
//     //connection to UART_TX and UART_RX(Module to module interconnect) Clear bit 2,1 and 0
//     SIM->SCGC4 = SIM->SCGC4|(1u<<10);//set bit 10 for giving clock to UART0
//     SIM->SCGC5 = SIM_SCGC5_PORTA_MASK;//set bit 9 for giving clock to PORTA
//     PORTA->PCR[1] = PORTA->PCR[1]&~(1u<<10)|(1u<<9)&~(1u<<8);//PTA1 as UART1_RX (010  9 for alternative 2 which is UART0_RX)
//     PORTA->PCR[2] = PORTA->PCR[1]&~(1u<<10)|(1u<<9)&~(1u<<8);//PTA2 as UART1_TX (010  9 for alternative 2 which is UART0_TX)
//     UART0->C2 = 0x00;//TX and RX both disabled to set baud rate
//     UART0->BDH = 0x00;//0x02;//Baud rate =9600,20.97152Mhz clock
//     UART0->BDL = 0x88;//BR=136//0x22;//BR=132.5=132=100111000
//     UART0->C1 = 0x00;
//     //UART0->S2=UART0->S1 & 0xC1;
//     UART0->C3 = 0x00;
//     UART0->C4 = 0x0F;//OSR=15//OSR=3
//     UART0->C5 = 0x00;//not both edges 0x02;//as OSR=4, sampling on both edges of baud rate clock of received data
//     UART0->C2 |= (1u<<3);//only TX enable
//     //UART0_C2=UART0_C2 | (1u<<2);//for RX pin to enable

// void InitLEDG(void)
// {
// 	SIM->SCGC5=SIM->SCGC5|SIM_SCGC5_PORTD_MASK;//Enable clock to PORTD
// 	PORTD->PCR[5]=256;//declare pins as GPIO
// 	GPIOD->PDDR=GPIOD->PDDR | 0x00000020;//set pin as output
// 	GPIOD->PDOR=GPIOD->PDOR | 0x00000020;//LED initially off
// }
// void InitSYSTICK(void)
// {
// 	//this is a 24 bit down counter
// 	SysTick->CTRL=0;//disable timer
// 	SysTick->LOAD=0x00FFFFFF;//load to full value 0x00FFFFFF
// 	SysTick->VAL=0;//write anything to reset register
// 	SysTick->CTRL=0x00000004;//1=bus clock, 0=disable interrupt, 0=disable systick
// }
// void delay(void)
// {
// 	SysTick->VAL=0;//reset counter
// 	SysTick->CTRL=0x00000005;//enable counter
// 	while((SysTick->CTRL & 0x00010000) == 0)//check flag
// 		{

// 		}

// }
// unsigned char UART_InChar(void)
// {

// 	while(UART0->S1 & (1u<<5))
// 	{
// 		return(UART0->D);
// 	}
// }
// void UART_OutChar(unsigned char data)
// {
// 	while(!(UART0->S1 & (1u<<7)));
// 	UART0->D = data;
// }
// // iterative method
// void UART_OutUDec(unsigned long n)
// {
// 	unsigned cnt=0;
// 	unsigned char buffer[11];
// 	do
// 	{
// 		buffer[cnt] = n%10;// digit
// 		n = n/10;
// 		cnt++;
// 	}	while(n);// repeat until n==0
// 	do
// 	{
// 		UART_OutChar(buffer[cnt-1]+'0');
// 		cnt--;
// 	}while(cnt != 0);
// }
// int main()
// {
// 	UART_Init();
// 	InitLEDG();
// 	InitSYSTICK();
// 	//unsigned long x=967;
// 	char name=UART_InChar();
// name=(char)((int)name+1);
// 		//UART_OutUDec(x);
// 		for(int i=0;i<1;i++)
// 		{
// 			UART_OutChar(name);
// 		}
// 		GPIOD->PDOR= 0u<<5;
// 		delay();
// 		GPIOD->PDOR= 1u<<5;
// 		delay();

// 	return 0;
// }

// #include "MKL46Z4.h"
// #include "stdlib.h"
// //#include "user_delay.h"

// #define str "Hello World!\n"

// extern uint32_t SystemCoreClock;

// void ClockInit(void)
// {
//     /* Enable clock for PORTA and UART0 */
//     SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
//     SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

//     /* Select clock source MCGFLLCLK */
//     SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
//     SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL(0);
// }
// void UART_Init(uint32_t baud)
// {
//     uint32_t sbr, osr, baudErr, diff_min;

//     /* Enable UART0_TX*/
//     PORTA->PCR[1] &= ~PORT_PCR_MUX_MASK;
//     PORTA->PCR[1] |= PORT_PCR_MUX(2);
//     /* Enable UART0_RX */
//     PORTA->PCR[2] &= ~PORT_PCR_MUX_MASK;
//     PORTA->PCR[2] |= PORT_PCR_MUX(2);

//     /* Disable the receiver and/or transmitter */
//     UART0->C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK);

//     /* Configure the baud rate */
//     sbr = (uint32_t)(SystemCoreClock/(baud * 4));
//     baudErr = abs((SystemCoreClock / (4 * sbr)) - baud);
//     osr = 3;
//     for (int i = 4; i <= 31; i++)
//     {
//         sbr = (uint32_t)(SystemCoreClock/(baud * (i+1)));
//         diff_min = abs((SystemCoreClock / ((i+1) * sbr)) - baud);
//         if (diff_min < baudErr)
//         {
//             baudErr = diff_min;
//             osr = i;
//         }
//     }

//     UART0->C4 &= ~UART0_C4_OSR_MASK;
//     UART0->C4 |= UART0_C4_OSR(osr);

//     sbr = (uint32_t)((SystemCoreClock)/(baud * ((UART0->C4 & UART0_C4_OSR_MASK) + 1)));

//     /* Save off the current value of the uartx_BDH except for the SBR field */
//     //UART0->BDH = UART0->BDH & ~(UART0_BDH_SBR(0x1F)) | UART0_BDH_SBR(((sbr & 0x1F00) >> 8));
//     if(sbr < 255u)
//     {
//         UART0->BDL = sbr;
//     }
//     else
//     {
//         UART0->BDL = 255u;
//         UART0->BDH = sbr - 255u;
//     }

//     /* Receiver and transmitter 8 bit */
//     UART0->C1 |= UART0_C1_M(0);
//     UART0->C4 |= UART0_C4_M10(0);

//     /* Enable the receiver and transmitter */
//     UART0->C2 |= (UART0_C2_TE_MASK | UART0_C2_RE_MASK );
// }

// void UartTxMsg(uint8_t *data)
// {
//     int i = 0;
//     while(data[i] != '\0')
//     {
//         UART0->D = data[i];
// 		// đợi thanh ghi D trống mới gửi data
//         while(!(UART0->S1 & (1ul<<6u))); /* Transmit complete */
//         i++;
//     }
// }
// //void UartRxMsg(uint8_t *data, uint8_t size)
// //{
// //    while(size--)
// //    {
// //    while (!(UART0->S1 & UART0_S1_RDRF_MASK));
// //    *data++ = UART0->D;
// //    }
// //}
// //uint8_t UartRxByte(void)
// //{
// //    while ((UART0->S1 & (1<<5)) == 0);
// //    return UART0->D;
// //}

// int main(void)
// {
//     ClockInit();
//     UART_Init(115200);
//     uint32_t i;

//     while(1)
//     {
//         UartTxMsg((uint8_t*)str);
//         for(i = 0; i < 8000000; i++){}
//     }
// }
//code for sending a string via uart method from board to pc via open sda port
#include "MKL46Z4.H"
#include "string.h"
# define len 40
void sw1(){
	SIM_SCGC5=SIM_SCGC5|SIM_SCGC5_PORTC_MASK;
	PORTC_PCR3=1u<<8|1u<<1|1u<<0;
	GPIOC_PDDR=GPIOC_PDDR&~(1u<<8);
}
void sw2(){
	SIM_SCGC5=SIM_SCGC5|SIM_SCGC5_PORTC_MASK;
	PORTC_PCR12=1u<<8|1u<<1|1u<<0;
	GPIOC_PDDR=GPIOC_PDDR&~(1u<<8);
}
void green()
{
	SIM_SCGC5=SIM_SCGC5|SIM_SCGC5_PORTD_MASK;
	PORTD_PCR5=1u<<8;
	GPIOD_PDDR=1u<<5;
	GPIOD_PSOR=1u<<5;
}
void red()
{
	SIM_SCGC5=SIM_SCGC5|SIM_SCGC5_PORTE_MASK;
	PORTE_PCR29=1u<<8;
	GPIOE_PDDR=1u<<29;
	GPIOE_PSOR=1u<<29;
}
void redon()
{
	GPIOE_PCOR=1u<<29;
}
void greenon()
{
	GPIOD_PCOR=(1u<<5);
}
void greenoff()
{
	GPIOD_PSOR=1u<<5;
}
void redoff()
{
	GPIOE_PSOR=1u<<29;
}
int sw1stat()
{
	if(GPIOC_PDIR==4096||GPIOC_PDIR==0)
	return 1;
	else
		return 0;
}
int sw2stat()
{
	if(GPIOC_PDIR==8||GPIOC_PDIR==0)
		return 1;
		else
			return 0;
}
int getgreenstatus()                             //READ DATA FROM PORT DATA INPUT REGISTER OF GREEN LED
{
	if( GPIOD_PDIR==1u<<5)
		return 0;
	else
		return 1;
}
int getredstatus()                             //READ DATA FROM PORT DATA INPUT REGISTER OF RED LED
{
	if( GPIOE_PDIR==1u<<29)
		return 0;
	else
		return 1;
}
void UART_Init(void){
	SIM_SOPT2=(1u<<26);//SIM_SOPT2_UART0SRC(1);Clock to UART0 MCGFLLCLK 20.97152MHz as MCG_C4=0x00 low range 20Mhz
	//SIM_SOPT5=0x00;kar na kar
	//open-drain mode disabled(Clear bit 16) plus
	//connection to UART_TX and UART_RX(Module to module interconnect) Clear bit 2,1 and 0
	SIM_SCGC4=SIM_SCGC4|(1u<<10);//set bit 10 for giving clock to UART0
	SIM_SCGC5=SIM_SCGC5_PORTA_MASK;//set bit 9 for giving clock to PORTA
	PORTA_PCR1=PORTA_PCR1&~(1u<<10)|(1u<<9)&~(1u<<8);//PTA1 as UART1_RX (010  9 for alternative 2 which is UART0_RX)
	PORTA_PCR2=PORTA_PCR1&~(1u<<10)|(1u<<9)&~(1u<<8);//PTA2 as UART1_TX (010  9 for alternative 2 which is UART0_TX)
	UART0_C2=0x00;//TX and RX both disabled
    UART0_BDH=0x00;//0x02;//Baud rate =9600,20.97152Mhz clock
    UART0_BDL=0x88;//BR=136//0x22;//BR=132.5=132=100111000
    UART0_C1=0x00;
    //UART0_S2=UART0_S1 & 0xC1;
    UART0_C3=0x00;
    UART0_C4=0x0F;//OSR=15//OSR=3
    UART0_C5=0x00;//not both edges 0x02;//as OSR=4, sampling on both edges of baud rate clock of received data
    UART0_C2=UART0_C2 | (1u<<3);//only TX enable
    //UART0_C2=UART0_C2 | (1u<<2);//for RX pin to enable
}

void InitSYSTICK(void)
{
	//this is a 24 bit down counter
	SysTick->CTRL=0;//disable timer
	SysTick->LOAD=0x00FFFFFF;//load to full value 0x00FFFFFF
	SysTick->VAL=0;//write anything to reset register
	SysTick->CTRL=0x00000004;//1=bus clock, 0=disable interrupt, 0=disable systick
}
void delay(void)
{
	SysTick->VAL=0;//reset counter
	SysTick->CTRL=0x00000005;//enable counter
	while((SysTick->CTRL & 0x00010000) == 0)//check flag
		{

		}

}
unsigned char UART_InChar(void)
{

	while(UART0->S1 & (1u<<5))
	{
		return(UART0->D);
	}
}
void UART_OutChar(unsigned char data)
{
	while(!(UART0->S1 & (1u<<7)));
	UART0->D=data;
}
// iterative method
void UART_OutUDec(unsigned long n)
{
	unsigned cnt=0;
	unsigned char buffer[11];
	do
	{
		buffer[cnt] = n%10;// digit
		n = n/10;
		cnt++;
	}	while(n);// repeat until n==0
	do
	{
		UART_OutChar(buffer[cnt-1]+'0');
		cnt--;
	}while(cnt != 0);
}
int main()
{
	green();
	red();

	redon();
	redoff();
	greenon();
	greenoff();
	UART_Init();
	InitSYSTICK();
	sw1();
	sw2();

    char msg[len]="udit kr agarwal";
    while(1)
    {
    	if(sw2stat()==1)
    		{greenon();redoff();}
    	else
    		{greenoff();redon();}
    	if(sw1stat()==1)
    	{
    		for(int i=0;i<len;i++)
    			UART_OutChar(msg[i]);
    		//UART0_C2=UART0_C2|(1u<<0);
    		while(sw1stat()==1);
    	}

    }

	return 0;

}
