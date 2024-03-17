#include <msp430.h>
#include "hardware.h"


void dma_init_uart(volatile uint8_t *rx_buffer)
{
    // Configure DMA channel 0
    __data20_write_long((uintptr_t) &DMA0SA, (uintptr_t)&UCA0RXBUF);    // Source single address
    __data20_write_long((uintptr_t) &DMA0DA, (uintptr_t)rx_buffer);     // Destination single address

    DMA0CTL  =  DMADT_4      |                  // Repeated single transfer
                DMADSTINCR_3 |                  // Destination address increment
                DMASWDW;                        // Source word to destination word

    DMA0SZ   = 32;                              // Block size
    DMACTL0 |= DMA0TSEL__UCA0RXIFG;             // DMA trigger is UART RX buffer interrupt
    DMACTL4  = DMARMWDIS;                       // Inhibited DMA transfers during read-modify-write CPU operations

    DMA0CTL |= DMAEN;                           // Enable DMA0
}

void dma_init_adc(volatile uint16_t *adc_buffer)
{
    // Configure DMA channel 2
    __data20_write_long((uintptr_t) &DMA2SA, (uintptr_t)&ADC12MEM0);    // Source single address
    __data20_write_long((uintptr_t) &DMA2DA, (uintptr_t)adc_buffer);    // Destination single address

    //DMALEVEL     |                  // Level sensitive (high level) trigger

    DMA2CTL  =  DMADT_4      |                  // Repeated single transfer
                DMASRCINCR_3 |                  // Source address incremented
                DMADSTINCR_3 |                  // Destination address increment --Don't increment destination address
                DMASWDW;                        // Source word to destination word

    DMA2SZ   = 2;                               // Block size
    DMACTL1 |= DMA2TSEL__ADC12IFG;              // DMA trigger is ADC interrupt
    DMACTL4  = DMARMWDIS;                       // Inhibited DMA transfers during read-modify-write CPU operations

    DMA2CTL |= DMAEN;                           // Enable DMA2
}
