/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "UART_driver.h"
#include "update_parse.h"
#include "update_QUEUE.h"

/*******************************************************************************
 * Codes
 ******************************************************************************/

#define SWITCH_ON                           0U
#define SWITCH_OFF                          1U
#define BUTTON_RESET_LEVEL                  (PTA->PDIR & (1U << 20U))
#define BUTTON1_LEVEL                       (PTC->PDIR & (1U << 12U))
#define CMD_REQUEST_UPDATE_FIRMWARE         "Request update firmware\r\n"
#define SIZE_CMD_REQUEST_UPDATE_FIRMWARE    27U

// int main()
// {
//     /* Enable clock gate port C */
//     SIM->SCGC5=(SIM->SCGC5 & (~SIM_SCGC5_PORTC_MASK)) |SIM_SCGC5_PORTC(1) ;
//     /* Set PTC12(sw2) as GPIO */
//     PORTC->PCR[12] = (PORTC->PCR[12] & (~PORT_PCR_MUX_MASK)) |PORT_PCR_MUX(1) |PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
//     /* Set PTC12 as input */
//     PTC->PDDR &= (~(1 << 12));
//     /* Check reset press */
//     if ( (BUTTON_RESET_LEVEL == SWITCH_ON) && (BUTTON1_LEVEL == SWITCH_ON))
//       while(1)
//       {

//          if ((BUTTON1_LEVEL == SWITCH_ON))
//         {
//         /* 1. UART0 send request update firmware to terminal */
//         UART_Init(115200);
//         UART_SendString(CMD_REQUEST_UPDATE_FIRMWARE,SIZE_CMD_REQUEST_UPDATE_FIRMWARE);
//         /* 2. Send App2.srec to kit and parse file. */
//         char * srecLine;
//         char * srecAddress;
//         char * srecData;

//         while (1)
//         {
//             /* Get srec line in queue */
//             if (QUEUE_Get(&srecLine) == true)
//             {
//                 /* Parse srec line */
//                 if ((SREC_Parser(srecLine, srecAddress, srecData ) == true))
//                 {
//                     /* Send ">>" to PC if Srec line is valid */
//                     UART_SendString(SREC_LINE_TRUE, SREC_LINE_TRUE_SIZE);

//                 }
//                 else
//                 {
//                     /* Send "Error" to PC if Srec line is invalid and stop program */
//                     UART_SendString(SREC_LINE_FALSE, SREC_LINE_FALSE_SIZE);
//                     NVIC_DisableIRQ(UART0_IRQn);
//                     break;
//                 }
//             }
//     }
//         // 3. Nạp file vào flash
//         // 4. Bấm reset để chạy App2.srec



//     }
//     else
//     {
//         // 1. Run App1.srec
//         // 2. Đợi người dùng bấm reset và sw2 để yêu cầu update firmware
//     }
//       }

// }

// void led()
// {
//     /* Enable clock gate to Port E */
//     SIM->SCGC5 |= SIM_SCGC5_PORTE(1);
//     /* Configure multiplex of PTC3(sw1), PTC12(sw2) and PTE29(led red) as GPIO */
//     PORTE->PCR[29] |= PORT_PCR_MUX(1);
//     /* Configure multiplex of PTE29(led red) as output, PTC3(sw1), PTC12(sw2) as input */
//     PTE->PDDR |=  (1 << 29 );
//     GPIOE->PCOR |= (1 << 29);
// }
// ////////////////////

int main()
{
    /* Enable clock gate port C */
    SIM->SCGC5=(SIM->SCGC5 & (~SIM_SCGC5_PORTC_MASK)) |SIM_SCGC5_PORTC(1) ;
    /* Set PTC12(sw2) as GPIO */
    PORTC->PCR[12] = (PORTC->PCR[12] & (~PORT_PCR_MUX_MASK)) |PORT_PCR_MUX(1) |PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    /* Set PTC12 as input */
    PTC->PDDR &= (~(1 << 12));
    /* Check reset press */
//    if ( (BUTTON_RESET_LEVEL == SWITCH_ON) && (BUTTON1_LEVEL == SWITCH_ON))

    uint8_t *getPtr = NULL;
    srec_parse_data_struct_t  parseData;
    srec_parse_error_t parseErrorCode = parseError_Undefined;

    if (QUEUE_GetData(&getPtr))
    {
        parseErrorCode = srec_parse(getPtr, &parseData);
        switch (parseErrorCode)
        {
        case parseError_Start:
            /* Xoa memory cua vung app */
            break;
        case parseError_Inprogress:
            //WriteToMemory(parseData.address, parseData.data[0],parseData.length);
            break;
        case parseError_Done:
            /* print thong tin DONE qua UART */
            UART_SendString(SREC_LINE_TRUE, SREC_LINE_TRUE_SIZE);
        default:
            /* print ma loi */
            break;
        }
    }
}
