#ifndef __ADC_H_
#define __ADC_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "MKL46Z4.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/**
 * @brief Function init ADC.
 * @param[in] instance
 * @param[in] channel
 * @return none
 */
void DRV_ADC_Init(uint8_t instance, uint8_t channel);

/**
 * @brief Get data result.
 * @param[in] instance
 * @return Data result
 */
uint16_t DRV_ADC_GetDataResult(uint8_t instance);

/**
 * @brief Function get conversion complete flag.
 * @param[in] instance
 * @return conversion complete flag
 */
bool DRV_ADC_GetConvCompleteFlag(uint8_t instance);

/**
 * @brief Function start conversion.
 * @param[in] instance
 * @return none
 */
void DRV_ADC_StartConv(uint8_t instance);

#endif /*__ADC_H_*/
