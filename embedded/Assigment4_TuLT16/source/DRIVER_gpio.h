#ifndef __DRIVER_GPIO_H
#define __DRIVER_GPIO_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "port_gpio.h"
#include "HAL_gpio.h"
#include "HAL_port.h"

/***********************************************************
@: Struct GPIO configration
************************************************************/
typedef struct
{
    PORT_Type               *portBase;
    GPIO_Type               *gpioBase;
    uint8_t                 pinIndex;
    PORT_Interrupt          portIntCfg;
    PORT_Mux                portMux;
    PORT_DriveStrength      portDriveStrength;
    bool                    portPassiveFilter;
    PORT_SlewRate           portSlewRate;
    PORT_PullSlect          portPullSlect;
    GPIO_Direct             gpiotDirect;
    GPIO_PIN_logic_level    gpioDefaultLogicLevel;
} Gpio_config;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/**
 * @brief: Init GPIO input(output)
 * @param[in]: gpioConfig array of pin configration
 * @param[in]: pinNumber
 * @return: None
 */
void DRV_InitGPIO(Gpio_config gpioConfig[], uint8_t pinNumber);

/**
 * @brier: Set PIN Direction
 * @param[in]: base of GPIOx (x as A...E)
 * @param[in]: Pin index
 * @param[in]: Direction of PIN input or output
 * @return: None
 */
void DRV_SetPinDirection(GPIO_Type * base, uint8_t pinIndex, GPIO_Direct direction);

/**
 * @brier: Set logic level of PIN as 1 or 0
 * @param[in]: base of GPIOx (x as A...E)
 * @param[in]: Pin index
 * @param[in]: Logic level
 *         PIN_LOGIC_HIGH: Set logic level of PIN as 1
 *         PIN_LOGIC_LOW: Set logic level of PIN as 0
 * @return: None
 */
void DRV_GPIO_WritePin(GPIO_Type * base, uint8_t pinIndex, GPIO_PIN_logic_level pinLogicLevel);

/**
 * @brier: Set logic level of multiple PIN
 * @param[in]: base of GPIOx (x as A...E).
 * @param[in]: pinIndex
 * @param[in]: pinLogicLevel
 * @return: None
 */
void DRV_GPIO_WritePins(GPIO_Type * base, uint32_t pinsVal);

/**
 * @brier: clear logic level to 0
 * @param[in]: base of GPIOx (x as A...E)
 * @param[in]: Pin index
 * @return: None
 */
void DRV_GPIO_ClearPin(GPIO_Type * base, uint8_t pinIndex);

/**
 * @brier: set logic level to 1
 * @param[in]: base of GPIOx (x as A...E)
 * @param[in]: Pin index
 * @return: None
 */
void DRV_GPIO_SetPin(GPIO_Type * base, uint8_t pinIndex);

/**
 * @brier: Toggle logic level of PIN
 * @param[in]: base of GPIOx (x as A...E).
 * @param[in]: Pin index
 * @return: None
 */
void DRV_GPIO_TogglePin(GPIO_Type * base, uint8_t pinIndex);

/**
 * @brier: Read logic level of PIN
 * @param[in]: base of GPIOx (x as A...E).
 * @param[in]: Pin index
 * @return: Logic level of PIN
 */
GPIO_PIN_logic_level DRV_GPIO_ReadPin(GPIO_Type * base, uint8_t pinIndex);

/**
 * @brier: Clear flag for external interrupt
 * @param[in]: base of PORTx (x as A...E).
 * @param[in]: Pin index
 * @return: None
 */
void DRV_PORT_ClearInterruptFlag(PORT_Type * base, uint8_t pinIndex);

/**
 * @brier: Read state flag for external interrupt
 * @param[in]: base of PORTx (x as A...E).
 * @param[in]: Pin index
 * @return: state flag
 */
uint32_t DRV_GetInterruptFlag(PORT_Type * base, uint8_t pinIndex);

#endif /* __DRIVER_GPIO_H*/
