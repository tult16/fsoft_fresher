#ifndef __PORT_GPIO_H
#define __PORT_GPIO_H

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "MKL46Z4.h"
#include <stdint.h>
#include <stdbool.h>

/***********************************************************
@: Logic level for Pin
************************************************************/
typedef enum {
    PIN_LOGIC_LOW    = 0,
    PIN_LOGIC_HIGH   = 1
} GPIO_PIN_logic_level;

/***********************************************************
@: Direction for Pin
************************************************************/
typedef enum
{
    GPIO_INPUT = 0,
    GPIO_OUTPUT
}GPIO_Direct;

/***********************************************************
@: State init GPIO
************************************************************/
typedef enum
{
    GPIO_STATE_SUCCESS = 0,
    GPIO_STATE_ERROR
} InitGPIO_State;

/***********************************************************
@: Type of port interrupt
************************************************************/
typedef enum
{
    PORT_INT_DMA_DISABLE    = 0X00,
    PORT_DMA_RISING_EDGE    = 0X01,
    PORT_DMA_FALLING_EDGE   = 0X02,
    PORT_DMA_EITHER_EDGE    = 0X03,
    PORT_INT_LOGIC_ZERO     = 0X08,
    PORT_INT_RISING_EDGE    = 0X09,
    PORT_INT_FALLING_EDGE   = 0XA,
    PORT_INT_EITHER_EDGE    = 0XB,
    PORT_INT_LOGIC_ONE      = 0X0C
} PORT_Interrupt;

/***********************************************************
@: Type of port mux
************************************************************/
typedef enum
{
    PORT_MUX_DISABLED    = 0x00,
    PORT_MUX_GPIO        = 0x01,
    PORT_MUX_ATT2        = 0x02,
    PORT_MUX_ALT3        = 0x03,
    PORT_MUX_ALT4        = 0x04,
    PORT_MUX_ALT5        = 0x05,
    PORT_MUX_ALT6        = 0x06,
    PORT_MUX_ALT7        = 0x007
} PORT_Mux;

/***********************************************************
@: Port drive strength
************************************************************/
typedef enum
{
    PORT_LOW_DRIVE_STRENGTH   = 0x00,
    PORT_HIGH_DRIVE_STRENGTH  = 0x01
} PORT_DriveStrength;

/***********************************************************
@: Port slew rate
************************************************************/
typedef enum
{
    PORT_FAST_SLEW_RATE   = 0x00,
    PORT_SLOW_SLEW_RATE   = 0x01
} PORT_SlewRate;

/***********************************************************
@: Port pull select
************************************************************/
typedef enum
{
    PORT_PULL_DISABLE       = 0x00,
    PORT_ENABLE_PULL_DOWN   = 0x01,
    PORT_ENABLE_PULL_UP     = 0x02
} PORT_PullSlect;

#endif /* __PORT_GPIO_H */
