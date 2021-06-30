#ifndef __INIT_PIT_H
#define __INIT_PIT_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include "MKL46Z4.h"

/*******************************************************************************
 * Defines
 ******************************************************************************/
#define PERIOD SystemCoreClock

/*******************************************************************************
 * Variables
 ******************************************************************************/
extern volatile uint32_t g_led1count ;
extern volatile uint32_t g_led2count ;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/**
 * @brief Function configration PIT.
 * @param[in] none
 * @return none
 */
void init_PIT();

/**
 * @brief Function enable timer PIT.
 * @param[in] none
 * @return none
 */
void start_PIT();

/**
 * @brief Function PIT handler.
 * @param[in] none
 * @return none
 */
void PIT_IRQHandler (void);

#endif /* __INIT_PIT_H */
