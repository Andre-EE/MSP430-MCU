#ifndef HARDWARE_H_
#define HARDWARE_H_

#include <stdint.h>

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

#endif /* HARDWARE_H_ */
