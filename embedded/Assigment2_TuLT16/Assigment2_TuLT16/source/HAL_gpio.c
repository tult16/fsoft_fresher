/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "HAL_gpio.h"

/*******************************************************************************
 * Codes
 ******************************************************************************/

/* Function read logic level for Pin.*/
bool HAL_GPIO_ReadPin(GPIO_Type * base, uint8_t pinIndex)
{
    return ((base->PDIR & (1 << pinIndex)) >> pinIndex);
}

/* Function set direction for pin */
void HAL_GPIO_SetDirection(GPIO_Type * base, uint8_t pinIndex, GPIO_Direct direction)
{
    base->PDDR = (base->PDDR & (uint32_t)(~(1 << pinIndex))) | (direction << pinIndex);
}

/* Function read direction for pin */
GPIO_Direct HAL_GPIO_ReadDirection(GPIO_Type * base, uint8_t pinIndex)
{
    return (GPIO_Direct)((base->PDDR & (uint32_t)(1 << pinIndex)) >> pinIndex);
}

/* Function set logic level for Pin */
void HAL_GPIO_WritePin(GPIO_Type * base, uint8_t pinIndex, GPIO_PIN_logic_level pinLogicLevel)
{
    base->PDOR = (base->PDOR & (uint32_t)(~(1 << pinIndex))) | (pinLogicLevel << pinIndex);
}

/* Function set logic level of multiple PINS */
void HAL_GPIO_WritePins(GPIO_Type * base, uint32_t pinsVal)
{
    base->PDOR = (base->PDOR & (~GPIO_PDOR_PDO_MASK)) | pinsVal;
}

/* Function toggle pin Logic level */
void HAL_GPIO_TogglePin(GPIO_Type * base, uint8_t pinIndex)
{
    base->PTOR = (uint32_t)(1 << pinIndex);
}

/* Function set Logic level 1 */
void HAL_GPIO_SetPin(GPIO_Type * base, uint8_t pinIndex)
{
    base->PSOR = (uint32_t)(1 << pinIndex);
}

/* Function clear to logic 0*/
void HAL_GPIO_ClearPin(GPIO_Type * base, uint8_t pinIndex)
{
    base->PCOR = (uint32_t)(1 << pinIndex);
}
