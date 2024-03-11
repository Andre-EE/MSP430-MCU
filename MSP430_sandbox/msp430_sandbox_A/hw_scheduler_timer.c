#include <msp430.h>
#include "hardware.h"

#define TICKS_PER_SECOND 32768
#define SLOTS_PER_SECOND 8

void scheduler_timer_init(void)
{
    TA0CTL |= TASSEL__ACLK;                         // Assign Timer A source to ACLK
    TA0CTL |= MC__UP;                               // Count Up Mode
    TA0CTL |= TACLR;                                // Clear the timer

    TA0CCR0 = TICKS_PER_SECOND / SLOTS_PER_SECOND;  // Ticks per slot
    TA0CCTL0 |= CCIE;                               // Enable interrupt
}

void scheduler_sleep(void)
{
    __bis_SR_register(LPM0_bits + GIE);     // Enter LPM0 w/ interrupt
    __no_operation();                       // For debugger
}

// TIMER0_A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR (void)
{
    __bic_SR_register_on_exit(LPM0_bits);           // Leave LPM0
    __no_operation();                               // For debugger
}
