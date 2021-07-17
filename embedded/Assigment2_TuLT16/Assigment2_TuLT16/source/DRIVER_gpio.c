/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "DRIVER_gpio.h"

/*******************************************************************************
 * Codes
 ******************************************************************************/

/* Function init array GPIO input*/
void DRV_InitGPIO(Gpio_config gpioConfig[], uint8_t pinNumber)
{
    uint8_t i;

    for (i = 0; i < pinNumber; i++)
    {
        /* Function set interrupt configration*/
        HAL_PORT_SetIntConfig(gpioConfig[i].portBase, gpioConfig[i].pinIndex, gpioConfig[i].portIntCfg);

        /* Function set pin as GPIO */
        HAL_PORT_MuxConfig(gpioConfig[i].portBase, gpioConfig[i].pinIndex, gpioConfig[i].portMux);

        /* Function set drive strength */
        HAL_PORT_SetDriveStrength(gpioConfig[i].portBase, gpioConfig[i].pinIndex, gpioConfig[i].portDriveStrength);

        /* Function config passiver filter */
        HAL_PORT_ConfigPassiveFilter(gpioConfig[i].portBase, gpioConfig[i].pinIndex, gpioConfig[i].portPassiveFilter);

        /* Function set slew rate */
        HAL_PORT_SetSlewRate(gpioConfig[i].portBase, gpioConfig[i].pinIndex, gpioConfig[i].portSlewRate);

        /* Function set pull select */
        HAL_PORT_SetPullSelect(gpioConfig[i].portBase, gpioConfig[i].pinIndex, gpioConfig[i].portPullSlect);

        /* Function set direction GPIO*/
        HAL_GPIO_SetDirection(gpioConfig[i].gpioBase, gpioConfig[i].pinIndex, gpioConfig[i].gpiotDirect);
        if (gpioConfig[i].gpiotDirect == GPIO_OUTPUT)
        {
            HAL_GPIO_WritePin(gpioConfig[i].gpioBase, gpioConfig[i].pinIndex, gpioConfig[i].gpioDefaultLogicLevel);
        }
    }
}

/* Function set pin direction */
void DRV_SetPinDirection(GPIO_Type * base, uint8_t pinIndex, GPIO_Direct direction)
{
    HAL_GPIO_SetDirection(base, pinIndex, direction);
}

/* Function write pin */
void DRV_GPIO_WritePin(GPIO_Type * base, uint8_t pinIndex, GPIO_PIN_logic_level pinLogicLevel)
{
    HAL_GPIO_WritePin(base, pinIndex, pinLogicLevel);
}
/* Function write array pins */
void DRV_GPIO_WritePins(GPIO_Type * base, uint32_t pinsVal)
{
    HAL_GPIO_WritePins(base, pinsVal);
}
/* Function set pin */
void DRV_GPIO_SetPin(GPIO_Type * base, uint8_t pinIndex)
{
    HAL_GPIO_SetPin(base, pinIndex);
}

/* Function clear pin */
void DRV_GPIO_ClearPin(GPIO_Type * base, uint8_t pinIndex)
{
    HAL_GPIO_ClearPin(base, pinIndex);
}

/* Function toggle pin */
void DRV_GPIO_TogglePin(GPIO_Type * base, uint8_t pinIndex)
{
    HAL_GPIO_TogglePin(base, pinIndex);
}

/* Function read logic pin */
GPIO_PIN_logic_level DRV_GPIO_ReadPin(GPIO_Type * base, uint8_t pinIndex)
{
    return (GPIO_PIN_logic_level)HAL_GPIO_ReadPin(base, pinIndex);
}

/* Function clear interrupt flag*/
void DRV_PORT_ClearInterruptFlag(PORT_Type * base, uint8_t pinIndex)
{
    HAL_PORT_ClearIntFlag(base, pinIndex);
}

/* Function get interrupt flag */
uint32_t DRV_GetInterruptFlag(PORT_Type * base, uint8_t pinIndex)
{
    return HAL_PORT_ReadIntFlag(base, pinIndex);
}
