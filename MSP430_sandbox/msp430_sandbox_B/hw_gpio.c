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

    // USCI_A0 UART pins
    P2SEL1 |=   BIT0 | BIT1;
    P2SEL0 &= ~(BIT0 | BIT1);

    // PWM output
    P3DIR  |= BIT4 | BIT5;                      // P3.4 and P3.5 -> output
    P3SEL0 |= BIT4 | BIT5;                      // P3.4 (TB0.3) and P3.5 (TB0.4) options select

    // SPI: UCB0
    P1SEL1 |= BIT3 | BIT6 | BIT7;               // P1.3 -> SS; P1.6 -> MOSI; P1.7 -> MISO
    P2SEL1 |= BIT2;                             // P2.2 -> CLK;

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
