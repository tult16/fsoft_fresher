#include "initPIT.h"

/* Function init PIT */
void init_PIT()
{
    /* PIT Peripheral Clock enable */
    SIM->SCGC6 |= SIM_SCGC6_PIT(1);
    NVIC_EnableIRQ(PIT_IRQn);
    /* active PIT module */
    PIT->MCR = (PIT->MCR & (~PIT_MCR_MDIS_MASK)) | PIT_MCR_MDIS(0);
    /* load timer period */
    PIT->CHANNEL[0].LDVAL   = PIT_LDVAL_TSV(PERIOD);
    /* enable interrupt and disable chain mode */
    PIT->CHANNEL[0].TCTRL = PIT_TCTRL_TIE(1) | PIT_TCTRL_CHN(0);
    // /* enable timer */
    // PIT->CHANNEL[0].TCTRL = (PIT->CHANNEL[0].TCTRL & (~PIT_TCTRL_TEN_MASK)) | PIT_TCTRL_TEN(1);
}

/* Function PIT IRQHandler */
void PIT_IRQHandler (void)
{
    g_led1count++;
    g_led2count++;
    /* clear the flag */
    PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
}

/* Function start timer PIT */
void start_PIT()
{
    /* enable timer */
    PIT->CHANNEL[0].TCTRL = (PIT->CHANNEL[0].TCTRL & (~PIT_TCTRL_TEN_MASK)) | PIT_TCTRL_TEN(1);
}

