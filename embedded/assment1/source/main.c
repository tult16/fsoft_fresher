/*******************************************************************************
 * Include
 ******************************************************************************/
#include "MKL46Z4.h"
#include <stdbool.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define PWM_PERIOD              10000U         /* Period pwm ~ 1ms */
#define PERIOD_1S               8000000U       /* Period ~ 1s */
#define SWITCH_ON               0U
#define SWITCH_OFF              1U
#define BUTTON1_LEVEL           (PTC->PDIR & (1U << 3U))
#define BUTTON2_LEVEL           (PTC->PDIR & (1U << 12U))
#define DUTY_ARRAY_MEMBER       5U
#define RED_LED_ON              GPIOE->PCOR |= (1 << 29)
#define RED_LED_OFF             GPIOE->PSOR |= (1 << 29)

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t g_CurrentMode = 1;           /* Set default mode 1 when start program */

/*******************************************************************************
 * Codes
 ******************************************************************************/
/* Function delay ms*/
void delay_ms(uint32_t m)
{
    uint32_t j;

    for (j = 0; j < m; j++)
    {
        __asm("nop");
    }
}

/* Function generate 1 PWM period ~ 1ms with each input duty */
void gen_one_pwm_period(uint8_t duty)
{
    uint32_t timeOn;
    timeOn = duty*PWM_PERIOD/100;      /* Time on led */
    RED_LED_ON;
    delay_ms(timeOn);
    RED_LED_OFF;
    delay_ms(PWM_PERIOD - timeOn);     /* Time off led */
}

/* Function mode 1: led red brighten */
void mode_one(void)
{
    uint8_t i, j;
    bool increase = false;

    while (1)
    {
        if (SWITCH_ON == BUTTON2_LEVEL)
        {
           g_CurrentMode = 2;
           break;
        }
        increase = !increase;
        for (i = 0; i <= 100; i+=10)    /* Loop increases duty each by 10% */
        {
            /* Change duty cycle for each 1s*/
            for (j = 0; j < PERIOD_1S/10/PWM_PERIOD; j++)
            {
                if (increase == true)
                {
                    gen_one_pwm_period(i);          /* Generate one pwm period with duty increases 0%,10%,20%,30%,40%,50%,60%,70%,80%,90%,100% */
                }
                else
                {
                    gen_one_pwm_period(100 - i);    /* Generate one pwm period with duty decrease 100%,90%,80%,70%,60%,50%,40%,30%,20%,10%,0% */
                }
            }
        }
    }
}

/* Function mode 2: led red light up with duty from 0%, 25%, 50%, 75%, 100% after return 0% */
void mode_two(uint8_t *count)
{
    uint8_t j;
    uint8_t dutyCycle[DUTY_ARRAY_MEMBER]= {0,25,50,75,100};

    while (1)
    {
        if (SWITCH_ON == BUTTON2_LEVEL)
        {
           g_CurrentMode = 1;
           break;
        }

        if (SWITCH_ON == BUTTON1_LEVEL)
        {
           (*count)++;/* Count is index array dutyCycle[] */
        }
        if (*count >= DUTY_ARRAY_MEMBER )
        {
            *count = 0;/* Reset count = 0 if count greater than or equal to DUTY_ARRAY_MEMBER */
        }
        /* Wait 0.5s to check button */
        for (j = 0; j < PERIOD_1S/2/10/PWM_PERIOD; j++)
        {
            gen_one_pwm_period(dutyCycle[*count]);
        }
    }
}

/* Function init Port C, Port E */
void init_pin(void)
{
    /* Enable clock gate to Port C,Port E */
    SIM->SCGC5 |= SIM_SCGC5_PORTC(1) | SIM_SCGC5_PORTE(1);

    /* Configure multiplex of PTC3(sw1), PTC12(sw2) and PTE29(led red) as GPIO */
    PORTE->PCR[29] |= PORT_PCR_MUX(1);
    PORTC->PCR[3]  |= PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    PORTC->PCR[12] |= PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;

    /* Configure multiplex of PTE29(led red) as output, PTC3(sw1), PTC12(sw2) as input */
    PTE->PDDR |=  (1 << 29 );
    PTC->PDDR &= (~(1 << 3)) & (~(1 << 12));
}

int main()
{
    uint8_t count = 0;    /* Count button presses*/

    init_pin();
    while(1)
    {
        switch (g_CurrentMode)
        {
            case 1:
                mode_one();
                break;
            case 2:
                mode_two(&count);
                break;
            default:
                break;
        }
    }

    return 0;
}
