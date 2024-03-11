# MSP430-MCU
Sandbox for a MSP430FR5969 design template

The goal is to have 2 MSP430 dev boards talk to each other over SPI. 

The general approach is the Cooperative Scheduler, described in ['Patterns for Time-Triggered Embedded Systems'](https://www.safetty.net/publications/pttes) by Michael Pont, which is available for free.

In this approach, interrupts are avoided, with the exception of a single interrupt that will create a time window for a task to be assigned to and completed during. To make this work with communication between devices, the DMA needs to be used and incoming and outgoing packets should be stored in appropriate data structures.

