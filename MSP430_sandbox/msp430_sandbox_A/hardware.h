#ifndef HARDWARE_H_
#define HARDWARE_H_

#include <msp430.h>
#include <stdint.h>
#include <stdio.h>

// GPIO
void gpio_init(void);
void gpio_toggle_red_led(void);
void gpio_toggle_grn_led(void);

// Clock system
void clock_init(void);

// Scheduler timer
void scheduler_timer_init(void);
void scheduler_sleep(void);

// UART
void uart_init(void);
void uart_ser_output(char *str);
void uart_ser_output_int(uint8_t value);
void uart_send_test_message(void);
void uart_trigger_tx(void);

// DMA
void dma_init_uart_rx(volatile uint8_t *rx_buffer);
void dma_init_uart_tx(volatile unsigned char *tx_buffer);
void dma_init_adc(volatile uint16_t *adc_buffer);
void dma_arm_uart_rx(void);
void dma_arm_uart_tx(void);
int  dma_get_arm_state_uart_rx(void);

// ADC
void adc_init(void);
void adc_trigger_conversion(void);

// PWM
void pwm_init(void);
void pwm_set_dc_0(void);
int  pwm_update_dc(int dc, int step);


#endif /* HARDWARE_H_ */
