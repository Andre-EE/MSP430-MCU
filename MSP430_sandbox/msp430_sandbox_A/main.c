#include <msp430.h> 
#include "hardware.h"
#include "scheduler.h"
#include "buffer.h"

#define BUFFER_SIZE 10

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// Initialize peripherals
	gpio_init();
	clock_init();
	scheduler_timer_init();
	uart_init();

	uart_init();

	uint8_t index_of_last_added_task;

	// Add LED tasks
	index_of_last_added_task = scheduler_add_task(gpio_toggle_grn_led, 0, 8);
	index_of_last_added_task = scheduler_add_task(gpio_toggle_red_led, 2, 4);

	simple_buffer_test();

    while(1)
    {
        scheduler_run();
        scheduler_sleep();
    }
	return 0;
}

void simple_buffer_test(void)
{
    uint8_t buffer[BUFFER_SIZE];

    // Initialize the circular buffer
    cbuf_handle_t cb = cbuf_init(buffer, BUFFER_SIZE);
    if (cb == NULL)
    {
        uart_ser_output("Failed to initialize circular buffer\r\n");
        return;
    }

    int i;
    // Put data into the circular buffer
    for (i = 0; i < BUFFER_SIZE + 5; i++)
    {
        int result = cbuf_put(cb, i); // Using overwrite to add more data than buffer size
        if (result == -1)
            uart_ser_output("Buffer is full. Overwriting oldest data.\r\n");
    }

    // Get data from the circular buffer and print it
    uart_ser_output("Data from circular buffer:\r\n");

    uint8_t data;
    size_t size;
    while (cbuf_get(cb, &data) == 0)
    {
        size = cbuf_get_size(cb);
        uart_ser_output_int(data);
        uart_ser_output("; size of buffer: ");
        uart_ser_output_int(size);
        uart_ser_output(" \r\n");

    }
    // Free the circular buffer
    cbuf_free(cb);
}
