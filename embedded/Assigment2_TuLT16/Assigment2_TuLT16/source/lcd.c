/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lcd.h"

/*******************************************************************************
 * Codes
 ******************************************************************************/

/* Function init LCD */
void LCD_Init(void)
{
    /* initialization sequence */
    LCD_Send_CMD(LCD_CMD_FUNCTION_SET);     /* function set: 8-bit data, 1-line, 5x8 font */
    LCD_Send_CMD(LCD_CMD_DISPLAY_CONTROL);  /* display control: move cursor right */
    LCD_Send_CMD(LCD_CMD_CLEAR_SCREEN);     /* clear screen, move cursor to home */
    LCD_Send_CMD(LCD_CMD_ENTRY_MODE_SET);   /* entry mode set: turn on display, cursor blinking */
}

/* Function send command to LCD */
void LCD_Send_CMD(uint8_t command)
{
    /* Function clear pin RS of LCD*/
    DRV_GPIO_ClearPin(GPIO_LCD_CONTROL_PORT, GPIO_LCD_PIN_RS_INDEX);

    /* Function clear pin RW of LCD */
    DRV_GPIO_ClearPin(GPIO_LCD_CONTROL_PORT, GPIO_LCD_PIN_RW_INDEX);

    /* Function send command to LCD */
    DRV_GPIO_WritePins(GPIO_LCD_DATA_PORT, GPIO_LCD_WRITE_DATA(command));

    /* Function clear pin enable */
    DRV_GPIO_ClearPin(GPIO_LCD_CONTROL_PORT, GPIO_LCD_PIN_EN_INDEX);

    /* Function delay 1ms */
    DRV_Delay(TIMEOUT_1MS);

    /* Function set pin enable */
    DRV_GPIO_SetPin(GPIO_LCD_CONTROL_PORT, GPIO_LCD_PIN_EN_INDEX);

    /* Function delay 1ms */
    DRV_Delay(TIMEOUT_1MS);

    /* Function claer pin enable */
    DRV_GPIO_ClearPin(GPIO_LCD_CONTROL_PORT, GPIO_LCD_PIN_EN_INDEX);

    /* Function delay wait until the command finishes */
    DRV_Delay(TIMEOUT_1MS);
}

/* Function send data to LCD */
void LCD_Send_Data(uint8_t data)
{
    /* Function clear pin RW of LCD*/
    DRV_GPIO_ClearPin(GPIO_LCD_CONTROL_PORT, GPIO_LCD_PIN_RW_INDEX);

    /* Function set pin RS of LCD*/
    DRV_GPIO_SetPin(GPIO_LCD_CONTROL_PORT, GPIO_LCD_PIN_RS_INDEX);

    /* Function send command to LCD */
    DRV_GPIO_WritePins(GPIO_LCD_DATA_PORT, GPIO_LCD_WRITE_DATA(data));

    /* Function clear pin EN of LCD*/
    DRV_GPIO_ClearPin(GPIO_LCD_CONTROL_PORT, GPIO_LCD_PIN_EN_INDEX);

    /* Function delay 1ms */
    DRV_Delay(TIMEOUT_1MS);

    /* Function set pin EN of LCD*/
    DRV_GPIO_SetPin(GPIO_LCD_CONTROL_PORT, GPIO_LCD_PIN_EN_INDEX);

    /* Function delay 1ms */
    DRV_Delay(TIMEOUT_1MS);

    /* Function clear pin EN of LCD*/
    DRV_GPIO_ClearPin(GPIO_LCD_CONTROL_PORT, GPIO_LCD_PIN_EN_INDEX);

        /* Function delay wait until the command finishes */
    DRV_Delay(TIMEOUT_1MS);
}

/* Function send string to LCD*/
void LCD_Send_String(uint8_t row, uint8_t col, char *str)
{
    uint8_t cmd;
    uint32_t i = 0;

    /* Move the cursor to the required position */
    cmd = ((row == LCD_LINE_1) ? LCD_CMD_CURSOR_FIST_LINE_ONE : LCD_CMD_CURSOR_LAST_LINE_ONE) + col - 1;
    LCD_Send_CMD(cmd);
    while(str[i]!=0)
    {
        LCD_Send_Data(str[i]);
        i++;
    }
}

/* Function shift string to left */
void LCD_ShiftLeft(uint8_t str_length)
{
    uint8_t i = 0;

    while (i < (str_length + LCD_MAX_COLUM))
    {
        DRV_Delay(TIMEOUT_500MS);
        LCD_Send_CMD(LCD_CMD_SHIFT_LEFT);
        i++;
    }
}

/* Function shift string to right */
void LCD_ShiftRight(uint8_t str_length)
{
    uint8_t i = 0;

    while (i < (str_length + LCD_MAX_COLUM))
    {
        DRV_Delay(TIMEOUT_500MS);
        LCD_Send_CMD(LCD_CMD_SHIFT_RIGHT);
        i++;
    }
}

/* Function delay ms */
void DRV_Delay(uint32_t tick)
{
    uint32_t j;

    for (j = 0; j < tick; j++)
    {
        __asm("nop");
    }
}
