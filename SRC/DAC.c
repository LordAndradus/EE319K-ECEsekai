// dac.c
// This software configures DAC output
// Runs on LM4F120 or TM4C123
// Program written by: Eva Nance
// Date Created: 7/7/2014 
// Last Modified:  5/2/2022
// Lab number: 10
// Hardware connections
//PC7-4, PD3-0

#include "tm4c123gh6pm.h"
#include <stdint.h>
// put code definitions for the software (actual C code)
// this file explains how the module works


// **************DAC_Init*********************
// Initialize 8-bit DAC, called once 
// Input: none
// Output: none
void DAC_Init(void){
//PC7-4, PD3-0
  SYSCTL_RCGCGPIO_R |= 0x0C;
	while((SYSCTL_RCGCGPIO_R & 0x0C) == 0) {}
	GPIO_PORTD_DIR_R = 0x0F;
	GPIO_PORTD_DEN_R = 0x0F;
	GPIO_PORTC_DIR_R = 0xF0;
	GPIO_PORTC_DEN_R = 0xF0;
}

// **************DAC_Out*********************
// output to DAC
// Input: 8-bit data
// Output: none
void DAC_Out(uint32_t data){
	GPIO_PORTD_DATA_R = (data & 0x0F); //Mask data to output into PortD's data register
	GPIO_PORTC_DATA_R = (data & 0xF0); //Mask data to output into PortC's data register
}	 
