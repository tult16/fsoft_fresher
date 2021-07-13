/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "UART_driver.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
//static char s_RxBuff[SREC_MAX_BYTE_COUNT] = {0};
uint8_t *putPtr = NULL;

/*******************************************************************************
 * Codes
 ******************************************************************************/

/* Function init UART with baudrate input */
void UART_Init(uint32_t baudRate)
{
    uint32_t sbr = 0;

    /* Enable clock gate port A */
    SIM->SCGC5 = (SIM->SCGC5 & (~SIM_SCGC5_PORTA_MASK)) | SIM_SCGC5_PORTA(1);
    /* Enable UART0_TX, PTA1 */
    PORTA->PCR[1] = (PORTA->PCR[1] & (~PORT_PCR_MUX_MASK)) |PORT_PCR_MUX(2);
    /* Enable UART0_RX, PTA2 */
    PORTA->PCR[2] = (PORTA->PCR[2] & (~PORT_PCR_MUX_MASK)) | PORT_PCR_MUX(2);
    /* Enable clock gate UART0 */
    SIM->SCGC4 = (SIM->SCGC4 & (~SIM_SCGC4_UART0_MASK)) | SIM_SCGC4_UART0(1);
    /* Select clock source MCGFLLCLK */
    SIM->SOPT2 = (SIM->SOPT2 & (~SIM_SOPT2_UART0SRC_MASK)) | SIM_SOPT2_UART0SRC(1);
    SIM->SOPT2 = (SIM->SOPT2 & (~SIM_SOPT2_PLLFLLSEL_MASK)) | SIM_SOPT2_PLLFLLSEL(0);
    /* Disable the receiver and/or transmitter before config */
    UART0->C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK);
    /* Receiver and transmitter 8 bit */
    UART0->C1 = (UART0->C1 & (~UART0_C1_M_MASK)) | UART0_C1_M(0);
    UART0->C4 = (UART0->C4 & (~(UART0_C4_M10_MASK))) | UART0_C4_M10(0);
    /* None parity*/
    UART0->C1 = (UART0->C1 & (~UART0_C1_PE_MASK)) | UART0_C1_PE(0);
    /* Send LSB first */
    UART0->S2 = (UART0->S2 & (~UART0_S2_MSBF_MASK)) | UART0_S2_MSBF(0);
    /* Receive and transmit data not inverted */
    UART0->S2 = (UART0->S2 & (~UART0_S2_RXINV_MASK)) | UART0_S2_RXINV(0);
    UART0->C3 = (UART0->C3 & (~UART0_C3_TXINV_MASK)) | UART0_C3_TXINV(0);
    /* select 1 stop bit */
    UART0->BDH = (UART0->BDH & (~UART0_BDH_SBNS_MASK)) | UART0_BDH_SBNS(0);

    /* Configure the baud rate (UARTn_BDH and UARTn_BDL) with OSR default 0xF */
    UART0->C4 = (UART0->C4 & (~(UART0_C4_OSR_MASK))) | UART0_C4_OSR(UART_OSR);
    sbr = UART_CLK/(UART_OSR +1)/baudRate;
    /* Set SBR */
    UART0->BDL = sbr & 0xFF;
    UART0->BDH = (sbr >> 8u) & 0x1F;

    /* Enable Tx,Rx and use hardware interrupt requested receiver */
    UART0->C2 = (UART0->C2 & (~(UART0_C2_TE_MASK | UART0_C2_RE_MASK  | UART0_C2_RIE_MASK))) | UART0_C2_TE_MASK | UART0_C2_RE_MASK | UART0_C2_RIE_MASK;

    /* Enable UART0 interrupt vector number */
    NVIC_EnableIRQ(UART0_IRQn);
}

/* Function sends string */
void UART_SendString(char *buff, uint8_t byteCount)
{
    uint8_t i;

    for (i = 0; i < byteCount; i++)
    {
        while (( UART0->S1 & UART0_S1_TDRE_MASK) == 0) {}
        UART0->D = buff[i];
    }

}

/* Function IRQ handler */
void UART0_IRQHandler(void)
{
    static uint8_t index = 0;
    QUEUE_GetUnuseElement(&putPtr);
    if ((UART0->S1 & UART0_S1_RDRF_MASK) == UART0_S1_RDRF_MASK)
    {
        // s_RxBuff[index] = UART0->D;
        // if (s_RxBuff[index] == '\n')
        // {
        //     QUEUE_Insert(s_RxBuff, index);
        //     index = 0;
        // }
        // else
        // {
        //     index++;
        // }
        putPtr[index] = UART0->D;
        index++;
        if (putPtr[index] == '\n')
        {
            QUEUE_Push();
            QUEUE_GetUnuseElement(&putPtr);
            index = 0;
        }
    }

}

