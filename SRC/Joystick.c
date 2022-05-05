#include <stdint.h>
#include <stdio.h>
#include "Joystick.h"
#include "inc/TM4C123GH6PM.h"

/*
Pin Connections:
GND - GND
+5V - VBus
PE1 - x
PE2 - y

range: 0 to 5V
Precision: 12-bits, so 4096
resolution: 5/4096 = 0.001220703125
*/

/* Samples from ADC, and places into private globals */
static uint16_t JXPos(void);
static uint16_t JYPos(void);
/* private globals */
static uint16_t x, y;
/* out-of-file variables */
uint8_t sampleReady = 0;

/*
Point of origin roughly: (2000, 2000), 0x(7D0, 7D0)
Relative to pins pointing right
0x000 = stick down, 	0xFFF = stick up
0x000 = stick right, 	0xFFF = stick left

In essence, its positioning would look like...
(0xFFF, 0xFFF)(0x7D0, 0xFFF)(0x000, 0xFFF)
(0xFFF, 0x7D0)(0x7D0, 0x7D0)(0x000, 0x7D0)
(0xFFF, 0x000)(0x7D0, 0x000)(0x000, 0x000)

deadzone...
Upper: 2400 (0x960)
Lower: 1600 (0x640)
*/

/* Catching values */
uint16_t getJX(void)
{
	return (x & 0xFFF);
}

uint16_t getJY(void)
{
	return (y & 0xFFF);
}

void JoystickInit()
{
	#define busClock 80000000
	//Init timer
	Timer2A_Init(busClock/8); //Samples every 80ms
	//Init ADC
	#define clock SYSCTL_RCGCGPIO_R
	SYSCTL_RCGCADC_R |= 0x03; //Turn on ADC0 & ADC1
	clock |= 0x10; //Turn on port E
	while((clock & 0x10) == 0);
	
	//Enable analog reads on PE1 and PE2
	GPIO_PORTE_DIR_R &= ~0x06;
	GPIO_PORTE_AFSEL_R |= 0x06;
	GPIO_PORTE_DEN_R &= ~0x06;
	GPIO_PORTE_AMSEL_R |= 0x06;
	
	//Initialize ADC0
	ADC0_PC_R = 0x01;				//Sample rate of 125KHz
	ADC0_SSPRI_R = 0x123; 	//Seq 3 is the highest priority, Seq 2 is the second priority
	ADC0_ACTSS_R &= ~0x08;	//Disable Sample Squencer 3
	ADC0_EMUX_R &= ~0xF000;	//Software triggered inputs
	ADC0_SSMUX3_R = (ADC0_SSMUX3_R & 0xFFFFFFF0) + 2; //PE1 (AIN2) 
	ADC0_SSCTL3_R = 0x06; 	//No Temperature Sensor or D0, but yes to IE0 and END0
	ADC0_IM_R &= ~0x08;			//Disable sequencer 3 interrupt
	
	//Initialize ADC1
	ADC1_PC_R = 0x01;				//Sample rate of 125KHz
	ADC1_SSPRI_R = 0x123; 	//Seq 3 is the highest priority, Seq 2 is the second priority
	ADC1_ACTSS_R &= ~0x08;	//Disable Sample Squencer 3
	ADC1_EMUX_R &= ~0xF000;	//Software triggered inputs
	ADC1_SSMUX3_R = (ADC1_SSMUX3_R & 0xFFFFFFF0) + 1; //PE2 (AIN1) 
	ADC1_SSCTL3_R = 0x06; 	//No Temperature Sensor or D0, but yes to IE0 and END0
	ADC1_IM_R &= ~0x08;			//Disable sequencer 3 interrupt
	
	//Activate ADC's
	ADC0_ACTSS_R |= 0x08;
	ADC1_ACTSS_R |= 0x08;
	sampleReady = 0;
}

void Timer2A_Init(uint32_t sampleRate)
{
	#define timerCLK SYSCTL_RCGCTIMER_R
	timerCLK |= 0x04;   // 0) activate timer2
	while((timerCLK & 0x04) == 0);

  TIMER2_CTL_R = 0x00000000;    // 1) disable timer2A during setup
  TIMER2_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER2_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER2_TAILR_R = sampleRate-1;    // 4) reload value
  TIMER2_TAPR_R = 0;            // 5) bus clock resolution
  TIMER2_ICR_R = 0x00000001;    // 6) clear timer2A timeout flag
  TIMER2_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R&0x00FFFFFF)|0x80000000; // 8) priority 4
// interrupts enabled in the main program after all devices initialized
// vector number 39, interrupt number 23
  NVIC_EN0_R = 1<<23;           // 9) enable IRQ 23 in NVIC
  TIMER2_CTL_R = 0x00000001;    // 10) enable timer2A
}

/* Sample gang */
void Timer2A_Handler(void)
{
	TIMER2_ICR_R = TIMER_ICR_TATOCINT; //Acknowledge timeout
	x = JXPos();
	y = JYPos();
	sampleReady = 1;
}

static uint16_t JXPos(void) //Samples from ADC0
{
	#define SQ3 0x08
	ADC0_PSSI_R = SQ3; 						 //Begin sequencer 3
	while((ADC0_RIS_R & SQ3) == 0); //Wait for conversion
	x = ADC0_SSFIFO3_R; 						 //Put the data into X
	ADC0_ISC_R = SQ3; 							 //Acknowledge we got the data.
	return x;
}
static uint16_t JYPos(void) //Samples from ADC1
{
	#define SQ3 0x08
	ADC1_PSSI_R = SQ3; 						 //Begin sequencer 3
	while((ADC1_RIS_R & SQ3) == 0); //Wait for conversion
	y = ADC1_SSFIFO3_R; 						 //Put the data into X
	ADC1_ISC_R = SQ3; 							 //Acknowledge we got the data.
	return y;
}
