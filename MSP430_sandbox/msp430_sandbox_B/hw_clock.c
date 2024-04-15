#include <msp430.h>
#include "hardware.h"

void clock_init(void)
{
    // Configure one FRAM waitstate as required by the device datasheet for MCLK
    // operation beyond 8MHz _before_ configuring the clock system.
    FRCTL0 = FRCTLPW | NWAITS_1;

    CSCTL0_H = CSKEY_H;                 // Unlock CS registers

    // Set DCO to 16MHz
    CSCTL1  = DCORSEL |                 // DCO range select
              DCOFSEL_4;                // Frequency select

    // Assign sources to clocks
    CSCTL2 = SELA__LFXTCLK |            // Assign ACLK source to LFXTCLK
             SELS__DCOCLK  |            // Assign SMCLK source to DCOCLK
             SELM__DCOCLK;              // Assign MCLK source to DCOCLK

    // Set clock dividers
    CSCTL3 = DIVA__1 |                  // ACLK  = LFXTCLK / 1  = 32.768 KHz
             DIVS__1 |                  // SMCLK = DCOCLK  / 1  = 16 MHz
             DIVM__16;                  // MCLK  = DCOCLK  / 16 = 1  MHz

    //CSCTL4 |= LFXTDRIVE_3;            // Change drive strength of LFXT (0-3)
    CSCTL4 &= ~LFXTOFF;                 // Clear the LFXTOFF bit of CTL4 to turn on LFXT

    do
    {
      CSCTL5  &= ~LFXTOFFG;             // Clear XT1 fault flag
      SFRIFG1 &= ~OFIFG;
    } while (SFRIFG1&OFIFG);            // Test oscillator fault flag

    CSCTL0_H = 0;                       // Lock CS registers

    //SFRIE1 |= OFIE;                   // Now that osc is running enable fault interrupt
}

