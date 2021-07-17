
/*******************************************************************************
 * Assignment 6
 * Name: Le Tuan Tu
 * Account: TuLT16
 * Descriptions:
 * Write a program to receive Srec file data sent from PC through UART0 module
 * of the FRD KL46Z256.
 * Parse each received Srec-line data and print out “>>” if success, print
 * out “Error” and stop program if error.
 * The UART configuration is:
 * Baud rate: 115200, Data bit: 8; Parity: None; Stop bits: 1;
 * Support “queue” for receiving each Srec-line data.
 * Requirement:
 * Require to separate the program to layers: App, Queue, Srec parse, UART0.
 * Not allow sharing any global variable  between layers. Not allow copying
 * way in queue functions.
 ******************************************************************************/


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "UART_driver.h"
#include "SrecParser.h"
#include "Queue.h"

/*******************************************************************************
 * Codes
 ******************************************************************************/
int main()
{
    char * srecLine;
    char * srecAddress;
    char * data;
    char data_length;
    char line[200] = {0};
    line[4] = ':';
    uint32_t address = 0;
    uint8_t AddTpm = 0;
    uint8_t i=0;
    uint8_t j=0;


    /* Function init UART0 with input baudrate */
    UART_Init(115200);

    while (1)
    {
        /* Get srec line in queue */
        if (QUEUE_Get(&srecLine) == true)
        {
            /* Parse srec line */
                if ((SREC_Parser(srecLine, srecAddress, data, &data_length) == true))
                {
                    /* Send ">>" to PC if Srec line is valid */
                    // line[5 + data_length] = '\r';
                    // line[5 + data_length + 1] = '\n';
                    for (i = 4; i < 8; i++)
                    {
                        AddTpm = (ConvertChar2Hex(srecLine[j]) <<4) + ConvertChar2Hex(line[j +1]);
                        address = (address << 8) | AddTpm;
                        j=j+2;
                    }
                    UART_SendString(&line[0], 5 + data_length + 1);
                }
            else
            {
                /* Send "Error" to PC if Srec line is invalid and stop program */
                UART_SendString(SREC_LINE_FALSE, SREC_LINE_FALSE_SIZE);
                NVIC_DisableIRQ(UART0_IRQn);
                break;
            }
        }
    }

    return 0;
}

addTemp = ((ConvertChar2Hex(test[i])) << 4) + ConvertChar2Hex(test[i+1]);
