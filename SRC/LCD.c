#include <stdint.h>
#include <stdio.h>
#include "inc/TM4C123GH6PM.h"
#include "LCD.h"

/* static functions */
/* Important LCD functions */
static void sendCommand(uint8_t command);
static void sendData(uint8_t data);

/*
Written by: Jo-michael Wallace
Date modified: 04/25/2022	
*/

/*
Hardware  connections, uses Port A
VCC 	- VBUS
GND 	- GND
CS 		- Pin 3(A) - SSI0Fss
RESET - Pin 7		 - GPIO
DC/RS - Pin 6		 - GPIO
MOSI	- Pin 5(A) - SSI0Tx
SCK		- Pin 2(A) - SSI0Clk
LED		- +3.3V
MISO	- Pin 4(A) - SSI0Rx, not really needed at the moment
*/

static void delay1ms(uint32_t period);

//Controls the font we use globally. Naturally, there is a choice for font specifics.
//uint8_t fontSelection = VCRmonoOSD;

//Initialize with SSI0
void LCDInit()
{
	//Enable Clocks
	SSIClock |= 0x01; //Turn on SSI 0
	SYSClock |= 0x01; //Turn on clock A
	while((SYSClock & 0x01) == 0);
	//Configure port
	GPIO_PORTA_DIR_R |= 0xC8; //PA{3,6,7} out
	GPIO_PORTA_AFSEL_R &= ~0xC8; //Disable alternative functions
	GPIO_PORTA_DEN_R |= 0xC8;
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0x00FF0FFF); //Make pins GPIO
	GPIO_PORTA_AMSEL_R &= ~0xC8;
	
	/*selectLCD;
	RSTHigh;
	delay1ms(500);
	RSTLow;
	delay1ms(500);
	RSTHigh;
	delay1ms(500);*/
	
	GPIO_PORTA_AFSEL_R |= 0x2C; //PA{2,3,5}
	GPIO_PORTA_DEN_R |= 0x2C;
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFF0F00FF)+0x00202200;
	GPIO_PORTA_AMSEL_R &= ~0x2C;
	
	/* Initialize and configure SSI0 */
	SSI0_CR1_R &= ~SSI_CR1_SSE; //Disable SSI for configuration
	SSI0_CR1_R &= ~SSI_CR1_MS; //Master mode
	//SSI0_CC_R = (SSI0_CC_R & SSI_CC_CS_M);
	SSI0_CC_R = (SSI0_CC_R & ~SSI_CC_CS_M) + SSI_CC_CS_SYSPLL; //Configure for System clock/PLL Baud Clockrate (AKA, let's configure to an 80MHz system)
	SSI0_CPSR_R = (SSI0_CPSR_R & ~SSI_CPSR_CPSDVSR_M) + 2; //Configure for 80MHz clock
	SSI0_CR0_R &= ~(SSI_CR0_SCR_M | SSI_CR0_SPH | SSI_CR0_SPO); 
	SSI0_CR0_R = (SSI0_CR0_R&~SSI_CR0_FRF_M)+SSI_CR0_FRF_MOTO;
	SSI0_CR0_R = (SSI0_CR0_R&~SSI_CR0_DSS_M)+SSI_CR0_DSS_8;
	SSI0_CR1_R |= SSI_CR1_SSE;
	
	//Reset LCD, wait 100ms so it listens to us.
	RSTLow;
	delay1ms(100);
	RSTHigh;
	
	//Software reset
	sendCommand(0x01);
	delay1ms(100);
	
	//Sleep out
	sendCommand(0x11);
	delay1ms(100);
	
	//Memory Access Control (MAC), sets the orientation of the dispaly, check how Bitmap data is stored and read before editting.
	/*
		Bit explainations:
		MY 	bit 7 - Row Addr (Y) order, 0 top-bottom, 1 bottom-top
		MX 	bit 6 - Column Addr (X) order
		MV 	bit 5 - Row/Column exchange 
		ML 	bit 4 - Vertical refresh order, 0 for top-bottom, 1 for bottom-top
		BGR bit 3 - 0 for RGB, 1 for BGR
		MH 	bit 2 - Horizontal refresh order, 1 for left-right, 0 for right-left
		RSV	bit 0 & 1 are reserved
	*/
	sendCommand(0x36); 
	sendData(0xE8);
	delay1ms(100);
	
	//Set pixel interfacing
	//D0 - D2: DBI (001 3bit/pixel (8-colors), 101 16bits/pixel, 110, 18bits/pixel, 111 24bits/pixel)
	//D4 - D6: DPI (Same ascribed above)
	//DBI - µController formatting, DPI - On-board LCD formatting.
	sendCommand(0x3A);
	//sendData(0x55);
	sendData(0x55); //18 bit, R(6) G(6) B(6)
	delay1ms(100);
	
	//Partial mode on
	sendCommand(0x12);
	delay1ms(100);
	
	//Display on
	sendCommand(0x29);
	delay1ms(100);
	
	//Set brightness
	sendCommand(0x51);
	sendData(0x0F);
	delay1ms(100);
	
	//Set brightness control
	sendCommand(0x53);
	sendData(0x2C);
	delay1ms(100);
	
	//set framerate
	sendCommand(0xB1);
	sendData(0xB0);
	sendData(0x1F);
	delay1ms(50);
	
	//Set background color
	selectLCD;
	blackBG();
	deselectLCD;
	delay1ms(100);
}

/* IMPORTANT functions */
static void sendCommand(uint8_t command)
{
	while((SSI0_SR_R & SSI_SR_BSY) == SSI_SR_BSY); //Wait until SPI line is not busy
	//WRX High
	//RDX High
	//D/Cx Low
	DCLow; //Send command
	SSI0_DR_R = command; //send out command
	while((SSI0_SR_R & SSI_SR_BSY) == SSI_SR_BSY); //Wait until SPI line is not busy
	return;
}

static void sendData(uint8_t data)
{
	while((SSI0_SR_R & SSI_SR_TNF) == 0); //Wait for Transmit FIFO to be full
	DCHigh; //Send data
	SSI0_DR_R = data; //Send out data
	return;
}

/* File specific functions */

//X - max: 480, Y - max: 320, therefore 2 bytes. Colors are 8-8-8, not enough for a full 32-bits.
void drawPixel(uint16_t x, uint16_t y, uint16_t color)
{
	setAddr(x, y, x, y);
	sendData(color >> 8);
	sendData((color & 0xFF));
}

void setAddr(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	selectLCD;
	//Check if it's over the LCD screen size limit
	x1 = (x1 > 320) ? 319 : x1;
	x2 = (x2 > 320) ? 319 : x2;
	y1 = (y1 > 240) ? 239 : y1;
	y2 = (y2 > 240) ? 239 : y2;
	//Set X
	sendCommand(0x2A);
	sendData(x1 >> 8);
	sendData(x1 & 0xFF);
	sendData(x2 >> 8);
	sendData(x2 & 0xFF);
	//Set Y
	sendCommand(0x2B);
	sendData(0x00);
	sendData(y1 & 0xFF);
	sendData(0x00);
	sendData(y2 & 0xFF);
	sendCommand(0x2C);
}

void setOrigin()
{
	//Set X
	sendCommand(0x2A);
	sendData(0x00);
	sendData(0x00);
	sendData(0x01);
	sendData(0x40);
	//Set Y
	sendCommand(0x2B);
	sendData(0x00);
	sendData(0x00);
	sendData(0x00);
	sendData(0xF0);
}

/* global functions */

void setBG(uint16_t Color)
{
	setAddr(0, 0, 0xFFFF, 0xFFFF);
	uint32_t BG = 76799;
	do
	{
		sendData((Color >> 8));
		sendData(Color & 0xFF);
	}while(BG--);
	sendCommand(0x00);
}

void whiteBG()
{
	setAddr(0, 0, 0xFFFF, 0xFFFF);
	uint32_t BG = 76799;
	do
	{
		sendData(0xFF);
		sendData(0xFF);
	}while(BG--);
	sendCommand(0x00);
}

void blackBG() //This is more like a transition screen
{
	setAddr(0, 0, 0xFFFF, 0xFFFF);
	uint32_t BG = 76799;
	do
	{
		sendData(0x00);
		sendData(0x00);
	}while(BG--);
	sendCommand(0x00);
}

void drawBitmap(uint8_t *data, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t padding, uint16_t offset)
{
	//Buffer is the image data, might need multiple calls to complete 1 image.
	uint16_t i = 0;
	uint16_t static j = 0; //Keeps track of y-lines we have drawn
	static uint16_t DataOffset = 0;
	static uint16_t XPos = 0; //Keeps track of last X position to avoid padding on next sector get
	//Find necessary components for a smooth print.
	uint16_t pitch = (width * 2); //How many pixels per line of width in the BMP, by multiple of 4
	
	sendCommand(0x3C); //Continue from last point of write
	
	while(j != height)
	{
		if(XPos == (pitch + DataOffset))
		{
			if(padding != 0)
			{
				i += 2;
				DataOffset += 2;
			}
			j++;
			XPos = 0;
			XPos += DataOffset;
		}
		
		if(i > 1023 - offset) break; //We have reached the limit of the IMG buffer
		
		sendData(data[i + 1]); //R5G3
		sendData(data[i]); //G3B5
		i += 2; //Fetch next pixel
		XPos += 2;

	}
	
	if(j >= height - 1)
	{
		DataOffset = 0;
		XPos = 0;
		j = 0;
	}
}

extern int32_t size;

void drawTransparentBitmap(uint8_t *data, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t padding, uint16_t offset)
{
	//Buffer is the image data, might need multiple calls to complete 1 image.
	uint16_t i = 0;
	uint16_t static j = 0; //Keeps track of y-lines we have drawn
	static uint16_t DataOffset = 0;
	static uint16_t XPos = 0; //Keeps track of last X position to avoid padding on next sector get
	//Find necessary components for a smooth print.
	uint16_t pitch = (width * 2); //How many pixels per line of width in the BMP, by multiple of 4
	
	uint16_t PX = x + ((XPos - DataOffset) / 2); //Pixel X position
	uint16_t PY = y; //Pixel Y position
	
	sendCommand(0x3C); //Continue from last point of write
	
	while(size > 0)
	{
		if(i > 1023 - offset) break; //We have reached the limit of the IMG buffer
		
		if(XPos == (pitch + DataOffset))
		{
			if(padding != 0)
			{
				i += 2;
				DataOffset += 2;
			}
			j++;
			PY++;
			XPos = 0;
			PX = x;
			XPos += DataOffset;
			size -= 2;
		}
		
		if(data[i] != 0xFF && data[i + 1] != 0xFF)
			drawPixel(PX, PY, (((uint16_t) data[i + 1]) << 8) + ((uint16_t) data[i]));
		
		PX++;
		XPos += 2;
		i += 2;
		size -= 2; //Subtract 2 bytes from the size
	}
	
	if(size <= 0)
	{
		DataOffset = 0;
		XPos = 0;
		j = 0;
	}
}

void ROMbitmap(const uint16_t *data, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
	uint16_t IDX = 0;
	uint16_t printY = y + height;
	uint16_t printX = x + width;
	setAddr(x, y, printX, printY);
	for(int i = x; i < printX; i++)
	{
		for(int j = y; j < printY; i++)
		{
			sendData((uint8_t) data[IDX] >> 8); //Push R5G3
			sendData((uint8_t) data[IDX]); //Push G3B5
			IDX++;
		}
	}
}

void drawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t Color)
{
	uint16_t i, j;
	setAddr(x, y, x + width, y + height); //Set address window to manipulate
	for(i = width + 1; i > 0; i--)
	{
		for(j = height + 1; j > 0; j--)
		{
			sendData(Color>> 8);
			sendData(Color & 0xFF);
		}
	}
}

void drawGradientRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t Color)
{
	uint16_t YPos = y;
	uint16_t XPos = x;
	setAddr(x, y, x + width, y + height);
	do
	{
		sendData((uint8_t) Color >> 8);
		sendData((uint8_t) Color & 0xFF);
		//Color -= 5; //Gradient turns to a new color
		XPos++;
		if(XPos > x + width)
		{
			if(YPos % 2 == 1)
				Color--; //Gradient turns into the lower shade
			YPos++;
			XPos = x;
		}
	}while(YPos < y + height);
}

void fastVLine(uint16_t x, uint16_t y, uint16_t height)
{
	uint16_t YPos = y;
	setAddr(x, y, x, y + height);
	do
	{
		sendData(0x00); sendData(0x00);
		YPos++;
	}while(YPos < y + height);
}

void drawLine(uint16_t x, uint16_t y, uint16_t width)
{
	uint16_t XPos = x;
	setAddr(x, y, x + width, y);
	do
	{
		sendData(0x00); sendData(0x00);
		XPos++;
	}while(XPos < x + width);
}

void drawWindow(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
	//Draw top left first
	drawLine(x, y, width); //Top line
	fastVLine(x, y, height); //left line
	fastVLine(x + width, y, height); //right line
	y += height; //bottom line
	drawLine(x, y, width);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MISC functions, but very useful
static void delay1ms(uint32_t period) //Tuned to 80MHz system
{
	period--;
	uint32_t time;
	while(period--)
	{
		time = 6665;
		while(time--);
	}
}
