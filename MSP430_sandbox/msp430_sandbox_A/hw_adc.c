#include <msp430.h>
#include "hardware.h"

void adc_init(void) //2 channel scan
{
    while(REFCTL0 & REFGENBUSY);                // If ref generator busy, WAIT
    REFCTL0   |= REFVSEL_2 | REFON;             // Select internal ref = 2.5V
                                                // Internal Reference ON
    // Configure ADC12
    ADC12CTL0 &= ~ADC12ENC;                     // Ensure conversion is disabled

    ADC12CTL0  = ADC12MSC |                     // Multiple SampleConversion
                 ADC12SHT0_2 |                  // S&H time = 16 ADC12CLK cycles for ch0-7 & ch24-31
                 ADC12SHT1_2 |                  // S&H time = 16 ADC12CLK cycles for ch8-23
                 ADC12ON;                       // ADC12 on
    ADC12CTL1  = ADC12CONSEQ_1|                 // Sequence-of-channels, single
                 ADC12SHP|                      // S&H pulse mode = sampling timer
                 ADC12SSEL_0;                   // ADCCLK = MODOSC
    ADC12CTL2 |= ADC12RES_2;                    // 12-bit conversion results
    ADC12CTL3  = ADC12TCMAP |                   // Enable internal temperature sensor
                 ADC12BATMAP;                   // Enable AVCC/2 reading
    ADC12MCTL0 = ADC12VRSEL_1 |                 // VR+ = VREF buffered, VR- = AVSS (single-ended, internal ref)
                 ADC12INCH_30;                  // Internal temperature sensor
    ADC12MCTL1 = ADC12VRSEL_1 |                 // VR+ = VREF buffered, VR- = AVSS (single-ended, internal ref)
                 ADC12INCH_31 |                 // AVCC/2 reading
                 ADC12EOS;                      // End of sequence

    ADC12CTL0 |= ADC12ENC;                      // Enable conversion

    while(!(REFCTL0 & REFGENRDY));              // Wait for reference generator to settle
}

void adc_trigger_conversion(void)
{
    ADC12CTL0 |= ADC12SC;                       // Start conversion-software trigger
}

//void adc_init(void) //single channel
//{
//    while(REFCTL0 & REFGENBUSY);                // If ref generator busy, WAIT
//    REFCTL0   |= REFVSEL_2 | REFON;             // Select internal ref = 2.5V
//                                                // Internal Reference ON
//    // Configure ADC12
//    ADC12CTL0 &= ~ADC12ENC;                     // Ensure conversion is disabled
//    ADC12CTL0  = ADC12SHT0_2 |                  // S&H time = 16 ADC12CLK cycles for ch0-7 & ch24-31
//                 ADC12SHT1_2 |                  // S&H time = 16 ADC12CLK cycles for ch8-23
//                 ADC12ON;                       // ADC12 on
//    ADC12CTL1  = ADC12CONSEQ_0|                 // Single-channel, single-conversion
//                 ADC12SHP|                      // S&H pulse mode = sampling timer
//                 ADC12SSEL_0;                   // ADCCLK = MODOSC
//    ADC12CTL2 |= ADC12RES_2;                    // 12-bit conversion results
//    ADC12CTL3  = ADC12TCMAP;                    // Enable internal temperature sensor
//
//    ADC12MCTL0 = ADC12VRSEL_1 + ADC12INCH_30;   // ADC input ch A30 => temp sense
//
//    ADC12CTL0 |= ADC12ENC;                      // Enable conversion
//    __no_operation();                           // For debugger
//    while(!(REFCTL0 & REFGENRDY));              // Wait for reference generator to settle
//}
