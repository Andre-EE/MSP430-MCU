#include "state_machine.h"

#define TX_BUFFER_SIZE 1024

//FSM variables
typedef enum {
    INIT,
    ADC_SAMPLE,
    PROCESS
} state_t;

static state_t current_state = INIT;

//DMA buffers
volatile unsigned char  rx_buffer[2];
volatile unsigned char  tx_buffer[TX_BUFFER_SIZE];
volatile uint16_t       adc_buffer[2];

//ADC variables
uint16_t mcu_temp = 0;
uint16_t mcu_ref  = 0;
uint16_t mcu_temp_result = 0;
uint16_t mcu_ref_result  = 0;
uint8_t  sample_count = 0;

//UART variables
uint16_t tx_buffer_pos = 0;

//function prototypes
void hardware_init(void);
void get_adc_samples(void);
void calculate_average_adc_values(void);
void process_uart(void);
void print_execute_task(void);
void print(unsigned char* message);
void print_selection(void);
void print_menu(void);
void print_adc_results(void);
void clear_screen(void);

//function implementation
void fsm_update_state(void)
{
    switch (current_state)
    {
        case INIT:
        {
            hardware_init();
            current_state = ADC_SAMPLE;
            break;
        }

        case ADC_SAMPLE:
        {
            get_adc_samples();
            sample_count++;

            if (sample_count == 15)
                current_state = PROCESS;
            break;
        }

        case PROCESS:
        {
            get_adc_samples();
            calculate_average_adc_values();
            process_uart();
            current_state = ADC_SAMPLE;
            break;
        }
    }
}

void hardware_init(void)
{
    // Initialize peripherals
    gpio_init();
    clock_init();
    scheduler_timer_init();
    uart_init();
    dma_init_uart_rx(rx_buffer);
    dma_init_uart_tx(tx_buffer);
    dma_init_adc(adc_buffer);
    adc_init();
}

void get_adc_samples(void)
{
    mcu_temp += adc_buffer[0];
    mcu_ref  += adc_buffer[1];
    adc_trigger_conversion();
}

void calculate_average_adc_values(void)
{
    mcu_temp_result = mcu_temp >> 4;
    mcu_ref_result  = mcu_ref  >> 4;
    mcu_temp = 0;
    mcu_ref  = 0;
    sample_count = 0;
}

void process_uart(void)
{
    if (dma_get_arm_state_uart_rx() == 0)
    {
        // Clear the transmit buffer
        uint16_t i = 0;
        for (i = 0; i < TX_BUFFER_SIZE; i++)
            tx_buffer[i] = 0;

        print_selection();

        if (rx_buffer[0] == '1')
            gpio_toggle_grn_led();
        else if (rx_buffer[0] == '2')
            gpio_toggle_red_led();
        else if (rx_buffer[0] == '3')
            print_adc_results();

        print_menu();
        print_execute_task();
    }
}

void print_execute_task(void)
{
    if (tx_buffer_pos > 0)
    {
        tx_buffer_pos = 0;
        dma_arm_uart_rx();
        dma_arm_uart_tx();
        uart_trigger_tx();
    }
}

void print(unsigned char* message)
{
    uint8_t i = 0;
    while (message[i] != '\0')
        tx_buffer[tx_buffer_pos++] = message[i++];
}

void print_selection(void)
{
    unsigned char temp_str[2] = {0};
    if (rx_buffer[0] != '0')
        temp_str[0] = rx_buffer[0];
        temp_str[1] = '\0';
        print(temp_str);
}

void print_menu(void)
{
    print("\r\n\r\nWelcome to MSP430 Menu \r\n\0");
    print("Select an option: \r\n\0");
    print("1. Toggle green LED\r\n\0");
    print("2. Toggle red LED\r\n\0");
    print("3. Print ADC results\r\n\0");
    print(">>> \0");
}

void print_adc_results(void)
{
    unsigned char row0[64] = {0};
    unsigned char row1[64] = {0};
    sprintf((char *)row0, "\r\nADC result for temperature reading: %d\0", mcu_temp_result);
    sprintf((char *)row1, "\r\nADC result for reference reading:   %d\0", mcu_ref_result);

    print(row0);
    print(row1);
}

void clear_screen(void)
{
    uint8_t i = 0;
    unsigned char blank_row[64] = "                                                          \r\n\0";

    for (i = 16; i > 0; i++)
        print(blank_row);

    dma_arm_uart_tx();
    uart_trigger_tx();
    tx_buffer_pos = 0;
}
