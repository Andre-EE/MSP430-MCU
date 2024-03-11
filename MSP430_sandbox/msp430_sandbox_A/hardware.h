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

#endif /* HARDWARE_H_ */
