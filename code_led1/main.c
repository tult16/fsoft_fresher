/*******************************************************************************
 * Include
 ******************************************************************************/
#include "MKL46Z4.h"
#include <stdbool.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define PWM_PERIOD              10000U         /* period pwm ~ 1ms */
#define PERIOD_1S               8000000U       /* period ~ 1s */
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
uint8_t g_CurrentMode = 1;      /* Set default mode 1 when start program */

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

/* Function generate 1 PWM period */
void gen_one_pwm_period(uint8_t duty)
{
    uint32_t timeOn;
    timeOn = duty*PWM_PERIOD/100;      /* time on led */
    RED_LED_ON;
    delay_ms(timeOn);
    RED_LED_OFF;
    delay_ms(PWM_PERIOD - timeOn);     /* time off led */
}

/* Function mode 1*/
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
        for (i = 0; i <= 100; i+=10)    /* loop increases duty each by 10% */
        {
            /* change duty cycle for each 1s*/
            for (j = 0; j < PERIOD_1S/10/PWM_PERIOD; j++)
            {
                if (increase == true)
                {
                    gen_one_pwm_period(i);          /* LED ON about 1s with duty 0%,10%,20%,30%,40%,50%,60%,70%,80%,90%,100% */
                }
                else
                {
                    gen_one_pwm_period(100 - i);    /* LED OF about 1s with duty 100%,90%,80%,70%,60%,50%,40%,30%,20%,10%,0% */
                }
            }
        }
    }
}

/* Function mode 2*/
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
           (*count)++;
        }
        if (*count >= DUTY_ARRAY_MEMBER )
        {
            *count = 0;
        }
        /* wait 0.5s to check button */
        for (j = 0; j < PERIOD_1S/2/10/PWM_PERIOD; j++)
        {
            gen_one_pwm_period(dutyCycle[*count]);
        }
    }
}

/* Function init Port C,D,E*/
void init_pin(void)
{
    /* Enable clock to Port C,Port E */
    SIM->SCGC5 |= SIM_SCGC5_PORTC(1) | SIM_SCGC5_PORTE(1) | SIM_SCGC5_PORTD(1);

    /* Configure multiplex of PTD5 and PTE29 as GPIO */
    PORTE->PCR[29] |= PORT_PCR_MUX(1);  /* make PTE29 LED pin as GPIO */
    PORTC->PCR[3]  |= PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;  /* make PTC3 pin as GPIO */
    PORTC->PCR[12] |= PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;  /* make PTC12 pin as GPIO */

    /* Configure multiplex of PTE 29 as output, PTC3, PTC12 as input */
    PTE->PDDR |=  (1 << 29 );                   /*Led RED output*/
    PTC->PDDR &= (~(1 << 3)) & (~(1 << 12));    /* set sw1, sw2 as input*/
}

int main()
{
    uint8_t count = 0;

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
