#ifndef __SYSTICK_CONFIG_H
#define __SYSTICK_CONFIG_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include "MKL46Z4.h"
#include "device.h"

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
extern uint32_t g_MsTicksLed1;
extern uint32_t g_MsTicksLed2;

/***********************************************************
@: Status of systick configration
************************************************************/
typedef enum
{
    STATUS_SUCCESS          = 0,
    STATUS_INVALID_PARAM    = 1
} status_t;

/*******************************************************************************
* Prototypes
 ******************************************************************************/

/**
 * @brief Function systick configration.
 * @param[in] none
 * @return STATUS_SUCCESS or STATUS_INVALID_PARAM.
 */
status_t SysTicks_Config(void);

/**
 * @brief Function systick handler.
 * @param[in] none
 * @return none.
 */
void SysTick_Handler(void);

#endif /* __SYSTICK_CONFIG_H */
