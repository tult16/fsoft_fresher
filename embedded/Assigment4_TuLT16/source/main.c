/*******************************************************************************
 Assignment 4
 Author: TuLT16
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "DRIVER_gpio.h"
#include "lcd.h"
#include "board_setting.h"
#include <string.h>
#include "MKL46Z4.h"
#include "DRIVER_adc.h"

/*******************************************************************************
 * Codes
 ******************************************************************************/
#define ADC0_INSTANCE               0
#define ADC_CHANNEL_LIGHT_SENSOR    3
#define ADC_VREF                    3300
#define ADC_RESOLUTION              12
#define ADC_CONVERT_RAW_DATA_TO_MV(x) (x*ADC_VREF/(1<<ADC_RESOLUTION -1))
#define ADC_SIZE_STRING_DATA_OUT    7

int main(void)
{
    uint16_t data_mv;
    char str_out[ADC_SIZE_STRING_DATA_OUT] = "     mv";

    /* Function enable clock gate port */
    BoardClockGate();
    /* Function init pin */
    DRV_InitGPIO(g_pinConfigArr, PIN_NUMBER);
    /* Function init LCD*/
    LCD_Init();
    /* Function int ADCO*/
    DRV_ADC_Init(ADC0_INSTANCE, ADC_CHANNEL_LIGHT_SENSOR);

    while(1)
    {
        /* Function start conversion ADC */
        DRV_ADC_StartConv(ADC0_INSTANCE);
        /* Get flag conversion complete */
        while (DRV_ADC_GetConvCompleteFlag(ADC0_INSTANCE) == false) {}
        /* Convert data output of ADC to millivolt*/
        data_mv = ADC_CONVERT_RAW_DATA_TO_MV(DRV_ADC_GetDataResult(ADC0_INSTANCE));
        /* Function convert data(int) to string */
        LCD_Int2String(data_mv, str_out);
        /* Function send data to LCD*/
        LCD_Send_String(LCD_LINE_1, LCD_COLUM_1, str_out);
        /* Function delay 500ms*/
        DRV_Delay(TIMEOUT_500MS);
    }
}
