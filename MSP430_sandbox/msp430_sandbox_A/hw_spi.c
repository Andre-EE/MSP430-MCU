#include <msp430.h>
#include "hardware.h"

void spi_init(void)
{
    // Configure USCI_B0 for SPI master operation
    UCB0CTLW0 = UCSWRST;                        // **Put state machine in reset**

    UCB0CTLW0 |=    UCMST   |                   // Master
                    UCSYNC  |                   // SPI-Mode (not UART)
                    //UCCKPL  |                   // Clock Polarity->High
                    UCMSB   |                   // MSB first
                    UCMODE_1|                   // USCI Mode 1: 4-pin SPI with UCxSTE active high: Slave enabled when UCxSTE = 1
                    UCSTEM;                     // USCI STE Mode (SS pin enable)

    UCB0CTLW0 |= UCSSEL__ACLK;                  // ACLK
    UCB0BR0 = 0x00;                             // USCI B0 Baud Rate 0 (low) divider
    UCB0BR1 = 0x00;                             // USCI B0 Baud Rate 1 (high)

    UCB0CTLW0 &= ~UCSWRST;                      // **Initialize USCI state machine**

    UCB0IFG &= ~UCTXIFG;
    UCB0IFG &= ~UCRXIFG;
}

void spi_trigger_tx(void)
{
    UCB0IFG &= ~UCTXIFG;
    UCB0IFG |= UCTXIFG;
}
