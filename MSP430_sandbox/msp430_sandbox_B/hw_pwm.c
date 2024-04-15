#include <msp430.h>
#include "hardware.h"

void pwm_init(void)
{
    TB0CCR0  = 100-1;                       // PWM Period = 16MHz/100 = 160KHz
    TB0CCTL3 = OUTMOD_7      |              // CCR3 reset/set
               CLLD_1;                      // Compare latch load source : 1 - TBR counts to 0
    TB0CCTL4 = OUTMOD_3      |              // CCR4 set/reset
               CLLD_1;                      // Compare latch load source : 1 - TBR counts to 0

    TB0CCR4  = 100;                         // CCR4 PWM duty cycle
    TB0CCR3  = 0;                           // CCR3 PWM duty cycle

    TB0CTL   = TBSSEL__SMCLK |              // Timer B clock source select: 2 - SMCLK
               MC__UP        |              // Timer B mode control: 1 - Up to CCR0
               TBCLGRP_1     |              // Timer B Group: 3-4, update control: 3
               TBCLR;                       // Timer B counter clear
}

void pwm_set_dc_0(void)
{
    TB0CCR4  = 100;                         // CCR4 PWM duty cycle
    TB0CCR3  = 0;                           // CCR3 PWM duty cycle
}

void pwm_set_dc(int dc)
{
    TB0CCR4  = dc;                          // CCR4 PWM duty cycle
    TB0CCR3  = dc;                          // CCR3 PWM duty cycle
}

int pwm_update_dc(int dc, int step)
{
    int current_dc = TB0CCR3;
    int r_val = 0;

    if (step > abs(current_dc - dc))
        step = 1;

    if (current_dc < dc)
        pwm_set_dc(current_dc + step);
    else if (current_dc > dc)
        pwm_set_dc(current_dc - step);
    else
        r_val = 1;

    return r_val;
}
