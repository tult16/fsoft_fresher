#include "MKL46Z4.h"
#include "SrecPase.h"

#define BAUD 115200
#define OSR  0xF
#define UART_CLK SystemCoreClock
/* Baud rate: 115200, Data bit: 8; Parity: None; Stop bits: 1; */

#define QUEUE_MAX_SIZE 5
char g_queue[QUEUE_MAX_SIZE][100] = {0};

int g_first_index = -1;
int g_last_index = -1;

void CopyBuffer(char *buffSrc, char *buffDest, uint8_t n);

void QUEUE_insert(char *str_buff, uint8_t byte_count)
{

    if (g_last_index == (QUEUE_MAX_SIZE -1))
    {
        g_last_index = -1;
        g_first_index = 0;
    }

    if (g_first_index == -1)
    {
        g_first_index = 0;
    }
    g_last_index++;
    CopyBuffer(str_buff, g_queue[g_last_index], byte_count);
    g_queue[g_last_index][byte_count-1] = '\0';
}

bool QUEUE_get(char **str_out)
{
    bool check;

    if ((g_first_index == -1) || (g_first_index > g_last_index))
    {
        /* queue is empty */
        check = false;
    }
    else
    {
        *str_out = g_queue[g_first_index];
        g_first_index++;
        check = true;
    }

    return check;
}


void UART_SendString(char *buff, uint8_t byteCount)
{
    uint8_t i;

    for (i = 0; i < byteCount; i++)
    {
        while (( UART0->S1 & UART0_S1_TDRE_MASK) == 0) {}
        UART0->D = buff[i];
    }

}

char g_RxBuff[100] = {0};
volatile bool g_end_of_srec = false;
void UART0_IRQHandler(void)
{
    static uint8_t index = 0;
    if ((UART0->S1 & UART0_S1_RDRF_MASK) == UART0_S1_RDRF_MASK)
    {
        g_RxBuff[index] = UART0->D;
        if (g_RxBuff[index] == '\n')
        {
            QUEUE_insert(g_RxBuff, index);
            index = 0;
        }
        else
        {
            index++;
        }
    }

}

void CopyBuffer(char *buffSrc, char *buffDest, uint8_t n)
{
    uint8_t j;
    for (j = 0; j < n; j++)
    {
        buffDest[j] = buffSrc[j];
    }
}

void UART_Init(void)
{
    uint16_t sbr;
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
    /* Receiver and transmitter 8 bit */
    UART0->C1 = (UART0->C1 & (~UART0_C1_M_MASK)) | UART0_C1_M(0);
    UART0->C4 = (UART0->C4 & (~(UART0_C4_M10_MASK | UART0_C4_OSR_MASK))) | UART0_C4_M10(0) | UART0_C4_OSR(0xF);
    /* None parity*/
    UART0->C1 = (UART0->C1 & (~UART0_C1_PE_MASK)) | UART0_C1_PE(0);
    /* Send LSB first */
    UART0->S2 = (UART0->S2 & (~UART0_S2_MSBF_MASK)) | UART0_S2_MSBF(0);
    /* Receive and transmit data not inverted */
    UART0->S2 = (UART0->S2 & (~UART0_S2_RXINV_MASK)) | UART0_S2_RXINV(0);
    UART0->C3 = (UART0->C3 & (~UART0_C3_TXINV_MASK)) | UART0_C3_TXINV(0);
    /* select 1 stop bit */
    UART0->BDH = (UART0->BDH & (~UART0_BDH_SBNS_MASK)) | UART0_BDH_SBNS(0);
    /* Configure the baud rate (UARTn_BDH and UARTn_BDL) */
    sbr = UART_CLK/(OSR +1)/BAUD;
    UART0->BDH = (sbr >> 8u) & 0x1F;
    UART0->BDL = sbr & 0xFF;
    /* enable Tx,Rx */
    UART0->C2 = (UART0->C2 & (~(UART0_C2_TE_MASK | UART0_C2_RE_MASK  | UART0_C2_RIE_MASK))) | UART0_C2_TE_MASK | UART0_C2_RE_MASK | UART0_C2_RIE_MASK;
    /* Enable UART0 interrupt vector number */
    NVIC_EnableIRQ(UART0_IRQn);
}

int main()
{
    char * srec_line;

    UART_Init();

    while (1)
    {
        if (QUEUE_get(&srec_line) == true)
        {
            if ((srecParse(srec_line) == true))
            {
                UART_SendString(">>\r\n", 4);
            }
            else
            {
                UART_SendString("error\r\n", 7);
                NVIC_DisableIRQ(UART0_IRQn);
                break;
            }
        }
    }

    return 0;
}
