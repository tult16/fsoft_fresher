#ifndef __LCD_H_
#define __LCD_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include "DRIVER_gpio.h"

/*******************************************************************************
 * Defines
 ******************************************************************************/
#define LCD_MAX_COLUM                   16u
#define LCD_LINE_1                      1u
#define LCD_COLUM_1                     1u

#define LCD_CMD_CLEAR_SCREEN            0X01
#define LCD_CMD_SHIFT_RIGHT             0x1C
#define LCD_CMD_SHIFT_LEFT              0x18
#define LCD_CMD_DISPLAY_CONTROL         0x06
#define LCD_CMD_FUNCTION_SET            0x30
#define LCD_CMD_ENTRY_MODE_SET          0x0C


#define LCD_CMD_CURSOR_FIST_LINE_ONE    0x80
#define LCD_CMD_CURSOR_LAST_LINE_ONE    0xC0

#define PERIOD_1S                       8000000U       /* Period ~ 1s */
#define TIMEOUT_1MS                     PERIOD_1S/1000
#define TIMEOUT_500MS                   PERIOD_1S/2

#define GPIO_LCD_PIN_RS_INDEX           2u    /* PTA2 */
#define GPIO_LCD_PIN_RW_INDEX           4u    /* PTA4 */
#define GPIO_LCD_PIN_EN_INDEX           5u    /* PTA5 */
#define GPIO_LCD_CONTROL_PORT           PTA  /* PTA */

#define GPIO_LCD_DATA_PORT              PTE  /* PTE */
#define GPIO_LCD_WRITE_DATA(cmd)        (cmd << 16)
#define GPIO_LCD_PIN_DATA_0_INDEX       16u  /* PTE16 */
#define GPIO_LCD_PIN_DATA_1_INDEX       17u  /* PTE17 */
#define GPIO_LCD_PIN_DATA_2_INDEX       18u  /* PTE18 */
#define GPIO_LCD_PIN_DATA_3_INDEX       19u  /* PTE19 */
#define GPIO_LCD_PIN_DATA_4_INDEX       20u  /* PTE20 */
#define GPIO_LCD_PIN_DATA_5_INDEX       21u  /* PTE21 */
#define GPIO_LCD_PIN_DATA_6_INDEX       22u  /* PTE22 */
#define GPIO_LCD_PIN_DATA_7_INDEX       23u  /* PTE23 */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/**
 * @brief Function init LCD.
 * @return none
 */
void LCD_Init(void);

/**
 * @brief Function send command to LCD.
 * @param[in] command.
 * @return none
 */
void LCD_Send_CMD(uint8_t command);

/**
 * @brief Function send data to LCD.
 * @param[in] data.
 * @return none
 */
void LCD_Send_Data(uint8_t data);

/**
 * @brief: Function send string data to LCD.
 * @param[in]: row of LCD
 * @param[in]: column of LCD
 * @param[in]: str string data
 * @return: none
 */
void LCD_Send_String(uint8_t row, uint8_t col, char *str);

/**
 * @brief Function shift left data on LCD.
 * @param[in] str_length.
 * @return none
 */
void LCD_ShiftLeft(uint8_t str_length);

/**
 * @brief Function shift right data on LCD.
 * @param[in] str_length.
 * @return none
 */
void LCD_ShiftRight(uint8_t str_length);

/**
 * @brief Function delay.
 * @param[in] tick.
 * @return none
 */
void DRV_Delay(uint32_t tick);

/**
 * @brief Function delay.
 * @param[in] int number, maximum is 4 number(9999).
 * @param[out] out string of input number
 * @return none
 */
void LCD_Int2String(uint16_t intNum, char *str);

#endif /*__LCD_H_*/
