#ifndef __INIT_LED_H
#define __INIT_LED_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include "MKL46Z4.h"
#include "device.h"

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
extern uint32_t g_Led1PulseWidth;
extern uint32_t g_Led2PulseWidth;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/**
 * @brief Function blink led setup.
 * @param[in] time1: timer value in miliseconds to blink led 1.
 * @param[in] time2: timer value in miliseconds to blink led 2.
 * @return none
 */
void Blink_led_setup(uint32_t time1, uint32_t time2);

/**
 * @brief Function start blink led(start systicks timer).
 * @param[in] none
 * @return none
 */
void Start_blink_led(void);

/**
 * @brief Function stop blink led(stop systicks timer).
 * @param[in] none
 * @return none
 */
void Stop_blink_led(void);

/**
 * @brief: Function toggle pin Logic level
 * @param[in]: base of GPIOx (x as A...E)
 * @param[in]: pinIndex
 * @return: none
 */
void ToggleLed(MCU_GPIO_Type * base, uint8_t pinIndex);

#endif /* __INIT_LED_H */
