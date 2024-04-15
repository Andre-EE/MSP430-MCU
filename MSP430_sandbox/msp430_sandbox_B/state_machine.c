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
volatile unsigned char  rx_buffer[8];
volatile unsigned char  tx_buffer[8];
volatile unsigned char  spi_buffer[4];
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

void print_execute_task(void);
void print(unsigned char* message);


//function implementation
void fsm_update_state(void)
{
    switch (current_state)
    {
        case INIT:
        {
            hardware_init();
            spi_buffer[0]    = 0x1;
            //dma_arm_rx();
            //dma_arm_tx();
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



            if (dma_get_arm_state_rx() == 0)
            {
                tx_buffer[0] = (mcu_temp_result >> 8) & 0xFF ;
                tx_buffer[1] = mcu_temp_result & 0xFF;
//                tx_buffer[2] = (mcu_temp_result >> 8) & 0xFF ;
//                tx_buffer[3] = mcu_temp_result & 0xFF;

                //tx_buffer[0] = 6;
                //tx_buffer[1] = 9;
                tx_buffer[2] = rx_buffer[0];
                tx_buffer[3] = rx_buffer[3];

//                tx_buffer[0] = rx_buffer[0];
//                tx_buffer[1] = 9;
//                tx_buffer[2] = 6;
//                tx_buffer[3] = rx_buffer[3];

//                tx_buffer[2] = rx_buffer[0];
//                tx_buffer[3] = rx_buffer[3];

                __no_operation();                               // For debugger
                dma_arm_tx();
                dma_arm_rx();


//                UCB0IFG &= ~UCRXIFG;
//                UCB0IFG &= ~UCTXIFG;
            }

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
    spi_init();
    dma_init_spi_tx(tx_buffer);
    dma_init_spi_rx(rx_buffer);
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
