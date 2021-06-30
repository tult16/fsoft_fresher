#ifndef __HAL_GPIO_H
#define __HAL_GPIO_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "port_gpio.h"

/*******************************************************************************
  * Prototypes
 *****************************************************************************/

/**
 * @brief Read Logic level for Pin.
 * @param[in] base: of GPIOx (x as A..E).
 * @param[in] pinIndex:
 * @return logic level of pin
 */
bool HAL_GPIO_ReadPin(GPIO_Type * base, uint8_t pinIndex);

/**
 * @brief: Set direction for pin
 * @param[in]: base of GPIOx (x as A..E)
 * @param[in]: pinIndex
 * @param[in]: direction for pin
 * @return: none
 */
void HAL_GPIO_SetDirection(GPIO_Type * base, uint8_t pinIndex, GPIO_Direct direction);

/**
 * @brief: Read direction for pin
 * @param [in]: base of GPIOx (x as A..E)
 * @param [in]: pinIndex
 * @return: input or output
 */
GPIO_Direct HAL_GPIO_ReadDirection(GPIO_Type * base, uint8_t pinIndex);

/**
 * @brief: Set Logic level for Pin
 * @param[in]: base of GPIOx (x as A..E)
 * @param[in]: pinIndex
 * @param[in]: logic level
 * @return: logic level of pin
 */
void HAL_GPIO_WritePin(GPIO_Type * base, uint8_t pinIndex, GPIO_PIN_logic_level pinLogicLevel);

/**
 * @brier: Set logic level of multiple PINS
 * @param[in]: base of GPIOx (x as A...E).
 * @param[in]: Pins value
 * @return: None
 */
void HAL_GPIO_WritePins(GPIO_Type * base, uint32_t pinsVal);

/**
 * @brief: Toggle pin Logic level
 * @param[in]: base of GPIOx (x as A...E)
 * @param[in]: pinIndex
 * @return: None
 */
void HAL_GPIO_TogglePin(GPIO_Type * base, uint8_t pinIndex);

/**
 * @brief: Set Logic level 1
 * @param[in]: base of GPIOx (x as A...E)
 * @param[in]: pinIndex
 * @return: None
 */
void HAL_GPIO_SetPin(GPIO_Type * base, uint8_t pinIndex);

/**
 * @brief: Clear to logic 0
 * @param[in]: base of GPIOx (x as A...E)
 * @param[in]: pinIndex
 * @return: None
 */
void HAL_GPIO_ClearPin(GPIO_Type * base, uint8_t pinIndex);

#endif /* __HAL_GPIO_H */
