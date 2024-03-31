#include <msp430.h>
#include "hardware.h"

void dma_init_uart_rx(volatile unsigned char *rx_buffer)
{
    // Configure DMA channel 0
    __data20_write_long((uintptr_t) &DMA0SA, (uintptr_t)&UCA0RXBUF);    // Source single address
    __data20_write_long((uintptr_t) &DMA0DA, (uintptr_t)rx_buffer);     // Destination single address

    DMA0CTL  =  //DMADT_4      |                  // Repeated single transfer
                DMADT_0      |                  // Single transfer
                DMASRCINCR_0 |                  // Source address doesn't increment
                DMADSTINCR_3 |                  // Destination address increment
                //DMASWDW;                        // Source word to destination word
                DMASBDB;                        // Source b to destination word

    DMA0SZ   = 2;                              // Block size
    DMACTL0 |= DMA0TSEL__UCA0RXIFG;             // DMA trigger is UART RX buffer interrupt
    DMACTL4  = DMARMWDIS;                       // Inhibited DMA transfers during read-modify-write CPU operations

    //DMA0CTL |= DMAEN;                           // Enable DMA0
}

void dma_arm_uart_rx(void)
{
    DMA0CTL |= DMAEN;
}

int dma_get_arm_state_uart_rx(void)
{
    return (DMA0CTL & DMAEN) == DMAEN;
}

void dma_init_uart_tx(volatile unsigned char *tx_buffer)
{
    // Configure DMA channel 1
    __data20_write_long((uintptr_t) &DMA1SA, (uintptr_t)tx_buffer);     // Source single address
    __data20_write_long((uintptr_t) &DMA1DA, (uintptr_t)&UCA0TXBUF);    // Destination single address

    DMA1CTL  =  DMADT_0      |                  // Single transfer
                DMASRCINCR_3 |                  // Source address increments
                DMADSTINCR_0 |                  // Destination address doesn't increment
                //DMASWDW;                        // Source word to destination word
                DMASBDB;                        // Source byte to destination byte

    DMA1SZ   = 1024;                             // Block size
    DMACTL0 |= DMA1TSEL__UCA0TXIFG;             // DMA trigger is UART TX buffer interrupt
    DMACTL4  = DMARMWDIS;                       // Inhibited DMA transfers during read-modify-write CPU operations

    //DMA1CTL |= DMAEN;                           // Enable DMA1
}

void dma_arm_uart_tx(void)
{
    DMA1CTL |= DMAEN;
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
