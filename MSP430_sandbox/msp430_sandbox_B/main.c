#include "state_machine.h"

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //simple_buffer_test();
    //tx_buffer = "Buffer is testing. data data. \r\n"

    uint8_t index_of_last_added_task;
    index_of_last_added_task = scheduler_add_task(fsm_update_state, 0, 1);

    while(1)
    {
        scheduler_run();
        scheduler_sleep();
    }
    return 0;
}
