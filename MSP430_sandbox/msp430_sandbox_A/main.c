#include <msp430.h> 
#include "hardware.h"
#include "scheduler.h"

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// Initialize peripherals
	gpio_init();
	clock_init();
	scheduler_timer_init();

	uint8_t index_of_last_added_task;

	// Add LED tasks
	index_of_last_added_task = scheduler_add_task(gpio_toggle_grn_led, 0, 8);
	index_of_last_added_task = scheduler_add_task(gpio_toggle_red_led, 2, 4);

    while(1)
    {
        scheduler_run();
        scheduler_sleep();
    }

	return 0;
}
