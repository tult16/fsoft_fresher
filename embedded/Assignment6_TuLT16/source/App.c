
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
#include "SrecPase.h"
#include "Queue.h"

/*******************************************************************************
 * Codes
 ******************************************************************************/
int main()
{
    char * srec_line;

    /* Function init UART0 with input baudrate */
    UART_Init(115200);

    while (1)
    {
        /* Get srec line in queue */
        if (QUEUE_get(&srec_line) == true)
        {
            /* Parse srec line */
            if ((SREC_Parse(srec_line) == true))
            {
                /* Send ">>" to PC if check srec line true  */
                UART_SendString(SREC_LINE_TRUE, SREC_LINE_TRUE_SIZE);
            }
            else
            {
                /* Send "Error" to PC if check srec line false and stop program */
                UART_SendString(SREC_LINE_FALSE, SREC_LINE_FALSE_SIZE);
                NVIC_DisableIRQ(UART0_IRQn);
                break;
            }
        }
    }

    return 0;
}
