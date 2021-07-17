/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "board_setting.h"

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
Gpio_config g_pinConfigArr[PIN_NUMBER] =
{
    /* LCD PIN RS - PTA2*/
    {
        .portBase = PORTA,
        .gpioBase = PTA,
        .pinIndex = 2,
        .portIntCfg = PORT_INT_DMA_DISABLE,
        .portMux = PORT_MUX_GPIO,
        .portDriveStrength = PORT_LOW_DRIVE_STRENGTH,
        .portPassiveFilter = false,
        .portSlewRate = PORT_SLOW_SLEW_RATE,
        .portPullSlect = PORT_ENABLE_PULL_UP,
        .gpiotDirect = GPIO_OUTPUT,
        .gpioDefaultLogicLevel = PIN_LOGIC_LOW
    },
    /* LCD PIN R/W  - PTA4*/
    {
        .portBase = PORTA,
        .gpioBase = PTA,
        .pinIndex = 4,
        .portIntCfg = PORT_INT_DMA_DISABLE,
        .portMux = PORT_MUX_GPIO,
        .portDriveStrength = PORT_LOW_DRIVE_STRENGTH,
        .portPassiveFilter = false,
        .portSlewRate = PORT_SLOW_SLEW_RATE,
        .portPullSlect = PORT_PULL_DISABLE,
        .gpiotDirect = GPIO_OUTPUT,
        .gpioDefaultLogicLevel = PIN_LOGIC_LOW
    },
    /* LCD PIN ENABLE - PTA5*/
    {
        .portBase = PORTA,
        .gpioBase = PTA,
        .pinIndex = 5,
        .portIntCfg = PORT_INT_DMA_DISABLE,
        .portMux = PORT_MUX_GPIO,
        .portDriveStrength = PORT_LOW_DRIVE_STRENGTH,
        .portPassiveFilter = false,
        .portSlewRate = PORT_SLOW_SLEW_RATE,
        .portPullSlect = PORT_PULL_DISABLE,
        .gpiotDirect = GPIO_OUTPUT,
        .gpioDefaultLogicLevel = PIN_LOGIC_LOW
    },
    /* LCD PIN 0 - PTE16 */
    {
        .portBase = PORTE,
        .gpioBase = PTE,
        .pinIndex = 16,
        .portIntCfg = PORT_INT_DMA_DISABLE,
        .portMux = PORT_MUX_GPIO,
        .portDriveStrength = PORT_LOW_DRIVE_STRENGTH,
        .portPassiveFilter = false,
        .portSlewRate = PORT_SLOW_SLEW_RATE,
        .portPullSlect = PORT_PULL_DISABLE,
        .gpiotDirect = GPIO_OUTPUT,
        .gpioDefaultLogicLevel = PIN_LOGIC_LOW
    },
    /* LCD PIN 1 - PTE17 */
    {
        .portBase = PORTE,
        .gpioBase = PTE,
        .pinIndex = 17,
        .portIntCfg = PORT_INT_DMA_DISABLE,
        .portMux = PORT_MUX_GPIO,
        .portDriveStrength = PORT_LOW_DRIVE_STRENGTH,
        .portPassiveFilter = false,
        .portSlewRate = PORT_SLOW_SLEW_RATE,
        .portPullSlect = PORT_PULL_DISABLE,
        .gpiotDirect = GPIO_OUTPUT,
        .gpioDefaultLogicLevel = PIN_LOGIC_LOW
    },
    /* LCD PIN 2 - PTE18 */
    {
        .portBase = PORTE,
        .gpioBase = PTE,
        .pinIndex = 18,
        .portIntCfg = PORT_INT_DMA_DISABLE,
        .portMux = PORT_MUX_GPIO,
        .portDriveStrength = PORT_LOW_DRIVE_STRENGTH,
        .portPassiveFilter = false,
        .portSlewRate = PORT_SLOW_SLEW_RATE,
        .portPullSlect = PORT_PULL_DISABLE,
        .gpiotDirect = GPIO_OUTPUT,
        .gpioDefaultLogicLevel = PIN_LOGIC_LOW
    },
    /* LCD PIN 3 - PTE19 */
    {
        .portBase = PORTE,
        .gpioBase = PTE,
        .pinIndex = 19,
        .portIntCfg = PORT_INT_DMA_DISABLE,
        .portMux = PORT_MUX_GPIO,
        .portDriveStrength = PORT_LOW_DRIVE_STRENGTH,
        .portPassiveFilter = false,
        .portSlewRate = PORT_SLOW_SLEW_RATE,
        .portPullSlect = PORT_PULL_DISABLE,
        .gpiotDirect = GPIO_OUTPUT,
        .gpioDefaultLogicLevel = PIN_LOGIC_LOW
    },
    /* LCD PIN 4 - PTE20 */
    {
        .portBase = PORTE,
        .gpioBase = PTE,
        .pinIndex = 20,
        .portIntCfg = PORT_INT_DMA_DISABLE,
        .portMux = PORT_MUX_GPIO,
        .portDriveStrength = PORT_LOW_DRIVE_STRENGTH,
        .portPassiveFilter = false,
        .portSlewRate = PORT_SLOW_SLEW_RATE,
        .portPullSlect = PORT_PULL_DISABLE,
        .gpiotDirect = GPIO_OUTPUT,
        .gpioDefaultLogicLevel = PIN_LOGIC_LOW
    },
    /* LCD PIN 5 - PTE21 */
    {
        .portBase = PORTE,
        .gpioBase = PTE,
        .pinIndex = 21,
        .portIntCfg = PORT_INT_DMA_DISABLE,
        .portMux = PORT_MUX_GPIO,
        .portDriveStrength = PORT_LOW_DRIVE_STRENGTH,
        .portPassiveFilter = false,
        .portSlewRate = PORT_SLOW_SLEW_RATE,
        .portPullSlect = PORT_PULL_DISABLE,
        .gpiotDirect = GPIO_OUTPUT,
        .gpioDefaultLogicLevel = PIN_LOGIC_LOW
    },
    /* LCD PIN 6 - PTE22 */
    {
        .portBase = PORTE,
        .gpioBase = PTE,
        .pinIndex = 22,
        .portIntCfg = PORT_INT_DMA_DISABLE,
        .portMux = PORT_MUX_GPIO,
        .portDriveStrength = PORT_LOW_DRIVE_STRENGTH,
        .portPassiveFilter = false,
        .portSlewRate = PORT_SLOW_SLEW_RATE,
        .portPullSlect = PORT_PULL_DISABLE,
        .gpiotDirect = GPIO_OUTPUT,
        .gpioDefaultLogicLevel = PIN_LOGIC_LOW
    },
    /* LCD PIN 7 - PTE23 */
    {
        .portBase = PORTE,
        .gpioBase = PTE,
        .pinIndex = 23,
        .portIntCfg = PORT_INT_DMA_DISABLE,
        .portMux = PORT_MUX_GPIO,
        .portDriveStrength = PORT_LOW_DRIVE_STRENGTH,
        .portPassiveFilter = false,
        .portSlewRate = PORT_SLOW_SLEW_RATE,
        .portPullSlect = PORT_PULL_DISABLE,
        .gpiotDirect = GPIO_OUTPUT,
        .gpioDefaultLogicLevel = PIN_LOGIC_LOW
    }
};

/*******************************************************************************
 * Codes
 ******************************************************************************/

/* Function enable clock gate to port A, port E */
void BoardClockGate(void)
{
    /* Enable clock gate to Port A, Port E */
    SIM->SCGC5 |= SIM_SCGC5_PORTA(1) | SIM_SCGC5_PORTE(1);
}
