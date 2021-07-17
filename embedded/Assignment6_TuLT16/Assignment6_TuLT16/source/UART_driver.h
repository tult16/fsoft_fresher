#ifndef _HEADER_UART_DRIVER_
#define _HEADER_UART_DRIVER_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include "MKL46Z4.h"
#include "Queue.h"

/*******************************************************************************
 * Defines
 ******************************************************************************/
#define UART_OSR  0xF
#define UART_CLK SystemCoreClock

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/**
 * @brief Function init UART0 with input baudrate.
 * @param[in] baudRate
 * @return none
 */
void UART_Init(uint32_t baudRate);

/**
 * @brief Function send string to PC.
 * @param[in] buff
 * @param[in] byteCount
 * @return none
 */
void UART_SendString(char *buff, uint8_t byteCount);

/**
 * @brief Function IRQ handler.
 * @param[in] none
 * @return none
 */
void UART0_IRQHandler(void);

#endif /* _HEADER_UART_DRIVER_ */
