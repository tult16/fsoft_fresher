/*******************************************************************************
 Assignment 2
 Author: TuLT16
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "DRIVER_gpio.h"
#include "lcd.h"
#include "board_setting.h"
#include <string.h>

/*******************************************************************************
 * Codes
 ******************************************************************************/

int main(void)
{
    uint8_t str_length;

    BoardClockGate();
    DRV_InitGPIO(g_pinConfigArr, PIN_NUMBER);
    LCD_Init();

    char *str_out = "FSOFT ACADEMY CODE YOUR LIFE";
    str_length = strlen(str_out);

    LCD_Send_String(LCD_LINE_1, LCD_MAX_COLUM, str_out);
    while(1)
    {
        LCD_ShiftLeft(str_length);
        DRV_Delay(PERIOD_1S);
        LCD_ShiftRight(str_length);
        DRV_Delay(PERIOD_1S);
    }
}


