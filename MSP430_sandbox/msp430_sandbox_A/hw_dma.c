#include <msp430.h>
#include "hardware.h"


void dma_init(volatile uint8_t *rx_buffer)
{
    // Configure DMA channel 0
    __data20_write_long((uintptr_t) &DMA0SA, (uintptr_t)&UCA0RXBUF);    // Source single address
    __data20_write_long((uintptr_t) &DMA0DA, (uintptr_t)rx_buffer);     // Destination single address

    DMA0CTL =   DMADT_4      |                  // Repeated single transfer
                DMADSTINCR_3 |                  // Destination address increment
                DMASWDW;                        // Source word to destination word

    DMA0SZ  = 32;                               // Block size
    DMACTL0 = DMA0TSEL__UCA0RXIFG;              // Source address in UART RX buffer
    DMACTL4 = DMARMWDIS;                        // Inhibited DMA transfers during read-modify-write CPU operations

    DMA0CTL |= DMAEN;                           // Enable DMA0
}
