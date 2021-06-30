#ifndef __HAL_PORT_H
#define __HAL_PORT_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "port_gpio.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/**
 * @brief Read logic level for Pin interrupt flag.
 * @param[in] base: of GPIOx (x as A..E).
 * @param[in] pinIndex
 * @return logic level of pin
 */
uint32_t HAL_PORT_ReadIntFlag(PORT_Type * base, uint8_t pinIndex);

/**
 * @brief Clear Pin interrupt flag.
 * @param[in] base: of GPIOx (x as A..E).
 * @param[in] pinIndex
 * @return none
 */
void HAL_PORT_ClearIntFlag(PORT_Type * base, uint8_t pinIndex);

/**
 * @brief Set interrupt configration.
 * @param[in] base: of GPIOx (x as A..E).
 * @param[in] pinIndex
 * @param[in] portInterrupt
 * @return none
 */
void HAL_PORT_SetIntConfig(PORT_Type * base, uint8_t pinIndex, PORT_Interrupt portInterrupt);

/**
 * @brief Read Pin interrupt configration.
 * @param[in] base: of GPIOx (x as A..E).
 * @param[in] pinIndex
 * @return Type of interrupt
 */
PORT_Interrupt HAL_PORT_ReadIntConfig(PORT_Type * base, uint8_t pinIndex);

/**
 * @brief Port mux configration.
 * @param[in] base: of GPIOx (x as A..E).
 * @param[in] pinIndex
 * @param[in]
 * @return none
 */
void HAL_PORT_MuxConfig(PORT_Type * base, uint8_t pinIndex, PORT_Mux portMux);

/**
 * @brief Read port mux configration.
 * @param[in] base: of GPIOx (x as A..E).
 * @param[in] pinIndex
 * @return configration pin at pinIndex
 */
PORT_Mux HAL_PORT_ReadMuxConfig(PORT_Type * base, uint8_t pinIndex);

/**
 * @brief Port mux configration.
 * @param[in] base: of GPIOx (x as A..E).
 * @param[in] pinIndex
 * @param[in] portDriveStrength
 * @return none
 */
void HAL_PORT_SetDriveStrength(PORT_Type * base, uint8_t pinIndex, PORT_DriveStrength portDriveStrength);

/**
 * @brief Port set drive strength enable.
 * @param[in] base: of GPIOx (x as A..E).
 * @param[in] pinIndex
 * @param[in] portDriveStrength
 * @return none
 */
void HAL_PORT_SetSlewRate(PORT_Type * base, uint8_t pinIndex, PORT_SlewRate portSlewRate);

/**
 * @brief Port set slew rate.
 * @param[in] base: of GPIOx (x as A..E).
 * @param[in] pinIndex
 * @param[in] portSlewRate
 * @return none
 */
void HAL_PORT_ConfigPassiveFilter(PORT_Type * base, uint8_t pinIndex, bool portPassiveFilter);

/**
 * @brief Port config passive filter.
 * @param[in] base: of GPIOx (x as A..E).
 * @param[in] pinIndex
 * @param[in] portPassiveFilter
 * @return none
 */

/**
 * @brief Port set pull select.
 * @param[in] base: of GPIOx (x as A..E).
 * @param[in] pinIndex
 * @param[in] portPullSlect
 * @return none
 */
void HAL_PORT_SetPullSelect(PORT_Type * base, uint8_t pinIndex, PORT_PullSlect portPullSlect);

#endif /* __HAL_PORT_H */
