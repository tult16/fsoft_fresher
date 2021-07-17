/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "HAL_port.h"

/*******************************************************************************
 * Codes
 ******************************************************************************/

/* Function config port Mux */
void HAL_PORT_MuxConfig(PORT_Type * base, uint8_t pinIndex, PORT_Mux portMux)
{
    base->PCR[pinIndex] = (base->PCR[pinIndex] & (~PORT_PCR_MUX_MASK)) | (PORT_PCR_MUX(portMux));
}

/* ReadIntFlag, TODO: correct the implementation */
uint32_t HAL_PORT_ReadIntFlag(PORT_Type * base, uint8_t pinIndex)
{
    return 0;
}

/* ClearIntFlag, TODO: correct the implementation */
void HAL_PORT_ClearIntFlag(PORT_Type * base, uint8_t pinIndex)
{

}

/* SetIntConfig, TODO: correct the implementation */
void HAL_PORT_SetIntConfig(PORT_Type * base, uint8_t pinIndex, PORT_Interrupt portInterrupt)
{

}

/* ReadIntConfig, TODO: correct the implementation */
PORT_Interrupt HAL_PORT_ReadIntConfig(PORT_Type * base, uint8_t pinIndex)
{
    return PORT_INT_DMA_DISABLE;
}

/* ReadMuxConfig, TODO: correct the implementation */
PORT_Mux HAL_PORT_ReadMuxConfig(PORT_Type * base, uint8_t pinIndex)
{
    return PORT_MUX_DISABLED;
}

/* SetDriveStrength, TODO: correct the implementation */
void HAL_PORT_SetDriveStrength(PORT_Type * base, uint8_t pinIndex, PORT_DriveStrength portDriveStrength)
{

}

/* SetSlewRate, TODO: correct the implementation */
void HAL_PORT_SetSlewRate(PORT_Type * base, uint8_t pinIndex, PORT_SlewRate portSlewRate)
{

}
/* ConfigPassiveFilter, TODO: correct the implementation */
void HAL_PORT_ConfigPassiveFilter(PORT_Type * base, uint8_t pinIndex, bool portPassiveFilter)
{

}

/* SetPullSelect, TODO: correct the implementation */
void HAL_PORT_SetPullSelect(PORT_Type * base, uint8_t pinIndex, PORT_PullSlect portPullSlect)
{

}

