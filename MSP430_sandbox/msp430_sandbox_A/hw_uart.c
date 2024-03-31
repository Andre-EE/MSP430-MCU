#include <msp430.h>
#include "hardware.h"

#define SMCLK_115200    0
#define SMCLK_9600      1
#define ACLK_9600       2

#define UART_MODE       SMCLK_115200

void uart_init(void)
{
    // Configure USCI_A0 for UART mode
    UCA0CTLW0 = UCSWRST;                        // Put eUSCI in reset

#if UART_MODE == SMCLK_115200

    UCA0CTLW0 |= UCSSEL__SMCLK;                 // CLK = SMCLK
    UCA0BR0 = 8;                                // 16000000/(16*115200)
    UCA0BR1 = 0x00;
    UCA0MCTLW |= UCOS16 | UCBRF_10 | 0xF700;    //0xF700 is UCBRSx = 0xF7

#elif UART_MODE == SMCLK_9600

    UCA0CTLW0 |= UCSSEL__SMCLK;                 // CLK = SMCLK
    UCA0BR0 = 104;                              // 16000000/(16*9600)
    UCA0BR1 = 0x00;
    UCA0MCTLW |= UCOS16 | UCBRF_2 | 0xD600;     //0xD600 is UCBRSx = 0xD6

#elif UART_MODE == ACLK_9600

    UCA0CTLW0 |= UCSSEL__ACLK;                  // CLK = ACLK
    UCA0BR0 = 3;                                // 32768/9600
    UCA0BR1 = 0x00;
    UCA0MCTLW |= 0x9200;                        //0x9200 is UCBRSx = 0x92

#else
    # error "Please specify baud rate to 115200 or 9600"

#endif

    UCA0CTLW0 &= ~UCSWRST;                      // Initialize eUSCI
    //UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt
}

void uart_ser_output(char *str)
{
    while (*str != 0)
    {
        while(!(UCA0IFG & UCTXIFG));
        UCA0TXBUF = *str++;
        __no_operation();
    }
}

void uart_ser_output_int(uint8_t value)
{
    char buffer[4];
    sprintf(buffer, "%d", value);
    uart_ser_output(buffer);
}

void uart_send_test_message(void)
{
    char text [] = "abcdefghijklmnopqrstuvwxyz7";
    uart_ser_output(text);
}

void uart_trigger_tx(void)
{
    UCA0IFG &= ~UCTXIFG;
    UCA0IFG |= UCTXIFG;
}
