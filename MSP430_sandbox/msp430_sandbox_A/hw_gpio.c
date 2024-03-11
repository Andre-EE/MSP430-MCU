#include <msp430.h>
#include "hardware.h"

void gpio_init(void)
{
    // External low frequency oscillator pins
    PJSEL0 |= BIT4 | BIT5;

    // LEDs
    P1OUT = 0;
    P4OUT = 0;
    P1DIR |= BIT0;
    P4DIR |= BIT6;

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;
}

void gpio_toggle_red_led(void)
{
    P4OUT ^= BIT6;
}

void gpio_toggle_grn_led(void)
{
    P1OUT ^= BIT0;
}
