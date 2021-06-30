/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "DRIVER_adc.h"

/*******************************************************************************
 * Definetions
 ******************************************************************************/
#define ADC_INSTANCE_NUM        1

/*******************************************************************************
 * Variables
 ******************************************************************************/
static ADC_Type *s_adcBaseAddr[ADC_INSTANCE_NUM] = ADC_BASE_PTRS;

/*******************************************************************************
 * Codes
 ******************************************************************************/
/* Function init ADCO */
void DRV_ADC_Init(uint8_t instance, uint8_t channel)
{
    /* software trigger, select voltage reference VREFH and VREFL */
    s_adcBaseAddr[instance]->SC2 |= ADC_SC2_ADTRG(0) | ADC_SC2_REFSEL(0);
    /* clock div by 4, long sample time, single ended 12 bit, bus clock */
    s_adcBaseAddr[instance]->CFG1 |= ADC_CFG1_ADIV(2)   |
                                     ADC_CFG1_ADICLK(0) |
                                     ADC_CFG1_MODE(1)   |
                                     ADC_CFG1_ADLSMP(1);
    /* select adc channel single-ended mode */
    s_adcBaseAddr[instance]->SC1[0] = ADC_SC1_ADCH(channel)| ADC_SC1_DIFF(0);
}

/* Function get data result */
uint16_t DRV_ADC_GetDataResult(uint8_t instance)
{
    return (s_adcBaseAddr[instance]->R[0]);
}

/* Function get conversion complete flag */
bool DRV_ADC_GetConvCompleteFlag(uint8_t instance)
{
    return (bool)((s_adcBaseAddr[instance]->SC1[0] & ADC_SC1_COCO_MASK) >> ADC_SC1_COCO_SHIFT);
}

/* Function start conversion by software trigger */
void DRV_ADC_StartConv(uint8_t instance)
{
    s_adcBaseAddr[instance]->SC1[0] |= 0;
}
