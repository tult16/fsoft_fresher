/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "UART_driver.h"
#include "update_parse.h"
#include "Queue.h"
#include "update_QUEUE.h"
#include "Flash.h"
#include "initSwitch.h"
/*******************************************************************************
 * Codes
 ******************************************************************************/

#define SWITCH_ON                           0U
#define SWITCH_OFF                          1U
#define BUTTON_RESET_LEVEL                  (PTA->PDIR & (1U << 20U))
#define BUTTON1_LEVEL                       (PTC->PDIR & (1U << 12U))
#define CMD_REQUEST_UPDATE_FIRMWARE         "Request update firmware\r\n"
#define SIZE_CMD_REQUEST_UPDATE_FIRMWARE    25U
#define APP_START_ADD                       0x0000A000
#define APP_SIZE                            2u

typedef void (*pFunction)(void);

void Bootloader_JumpToApp(void)
{
    volatile uint32_t appStack;
    pFunction appEntry;

    /* reconfigure vector table offset register to match the application */
    SCB->VTOR = APP_START_ADD;
    /* get the app stack pointer */
    appStack = Read_FlashAddress(APP_START_ADD);
    /* set application stack pointer */
    __set_MSP(appStack);
    /* get app entry pointer */
    appEntry = (pFunction)Read_FlashAddress(APP_START_ADD + 4);
    /* start application */
    appEntry();
}

srec_parse_error_t status;

int main()
{
    // char * srecLine = NULL;
    uint8_t * srecLine = NULL;
    srec_parse_data_struct_t output;
    uint8_t dataIndex=0;

    initSwitch();
    /* Check reset press */
    if ((BUTTON1_LEVEL == SWITCH_ON))
    {
        /* 1. UART0 send request update firmware to terminal */
        UART_Init(115200);
        UART_SendString(CMD_REQUEST_UPDATE_FIRMWARE,SIZE_CMD_REQUEST_UPDATE_FIRMWARE);
        Erase_Multi_Sector(APP_START_ADD , APP_SIZE);
        /* 2. Send App2.srec to kit and parse file. */
        while (1)
        {
            /* Get srec line in queue */
            // if (QUEUE_Get(&srecLine) == true)
            if (QUEUE_GetData(&srecLine) == true)
            {
                /* Parse srec line */
                status = srec_parse(srecLine, &output);
                switch (status)
                {
                    case parseError_Start:
                        break;
                    case parseError_Inprogress:
                        for (dataIndex = 0; dataIndex < output.length; dataIndex+=4)
                        {
                            __disable_irq();
                            Program_LongWord_8B((output.address+ dataIndex), &(output.data[dataIndex]));
                            __enable_irq();
                        }
                        break;
                    case parseError_Done:
                        UART_SendString(SREC_LINE_TRUE, SREC_LINE_TRUE_SIZE);
                        Bootloader_JumpToApp();
                        break;
                    case parseError_Invalid:
                    case parseError_InvalidChecksum:
                    case parseError_InvalidSrecType:
                        /* Send "Error" to PC if Srec line is invalid and stop program */
                        UART_SendString(SREC_LINE_FALSE, SREC_LINE_FALSE_SIZE);
                        NVIC_DisableIRQ(UART0_IRQn);
                        break;
                    default:
                        break;
                }
                QUEUE_Pop();
            }

        }
    }
    else
    {
        Bootloader_JumpToApp();
    }

    return 0;
}

// int main()
// {
//     /* Enable clock gate port C */
//     SIM->SCGC5=(SIM->SCGC5 & (~SIM_SCGC5_PORTC_MASK)) |SIM_SCGC5_PORTC(1) ;
//     /* Set PTC12(sw2) as GPIO */
//     PORTC->PCR[12] = (PORTC->PCR[12] & (~PORT_PCR_MUX_MASK)) |PORT_PCR_MUX(1) |PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
//     /* Set PTC12 as input */
//     PTC->PDDR &= (~(1 << 12));
//     /* Check reset press */
// //    if ( (BUTTON_RESET_LEVEL == SWITCH_ON) && (BUTTON1_LEVEL == SWITCH_ON))
//     UART_Init(115200);

//     uint8_t *getPtr = NULL;
//     srec_parse_data_struct_t  parseData;
//     srec_parse_error_t parseErrorCode = parseError_Undefined;
//     while(1)
//     {
// //        UART_SendString(CMD_REQUEST_UPDATE_FIRMWARE,SIZE_CMD_REQUEST_UPDATE_FIRMWARE);
//         if (QUEUE_GetData(&getPtr))
//         {
//             parseErrorCode = srec_parse(getPtr, &parseData);
//             switch (parseErrorCode)
//             {
//             case parseError_Start:
//                 /* Xoa memory cua vung app */
//                 break;
//             case parseError_Inprogress:
//                 //WriteToMemory(parseData.address, parseData.data[0],parseData.length);
//                 QUEUE_Pop();
//                 break;
//             case parseError_Done:
//                 /* print thong tin DONE qua UART */
//                 UART_SendString(SREC_LINE_TRUE, SREC_LINE_TRUE_SIZE);
//             default:
//                 /* print ma loi */
//                 break;
//             }
//         }

//     }
// }
