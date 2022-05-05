#include <stdint.h>
#include <stdio.h>
#include "inc/TM4C123GH6PM.h"
#include "inc/PLL.h"
#include "FlashProgram.h"
#include "Joystick.h"
#include "LCD.h"
#include "Math.h"
#include "SDCard.h"
#include "LoadImage.h"
#include "DAC.h"
#include "Sound.h"

extern void GameLoop(void);
void Menu(void);
void ButtonInit(void);
static void delay1ms(uint32_t period);
static void DInt(void);
static void EInt(void);
void checkPushA(void);
void checkPushB(void);


static uint16_t menuX;
static uint16_t menuY;
static uint16_t sampleY;
static uint8_t buttonPushed = 0; //Checks if the button has been pushed
static uint8_t buttonPushedB = 0;

extern uint8_t SPC;
extern uint8_t SF;

extern uint8_t loaded;
extern void loadGame(void);

void ButtonInit()
{
		SYSCTL_RCGCGPIO_R |= 0x20;
    while((SYSCTL_RCGCGPIO_R & 0x20) == 0){}
    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY; //Unlock GPIO for PortF
    GPIO_PORTF_CR_R = 0x11; //Enables changes for PF4 and PF0

    GPIO_PORTF_DIR_R &= ~(0x11); //Pins 4 and 0 are inputs to the Switches.
    GPIO_PORTF_DEN_R |= 0x11; //Enable digital signals to PF{4,0}
    GPIO_PORTF_PUR_R |= 0x11; //Turn on pull-up resistors to ground for Pins 4 and 0 for Port F.
}

void InitEverything()
{
	DInt();
	PLL_Init(Bus80MHz);
	JoystickInit();
	do
	{
		InitSD();
	}while(SF != 1); //Gonna trust you that the card is proper!
	randInit();
	LCDInit();
	ButtonInit();
	DAC_Init();
	EInt();
}

int main(void)
{
	InitEverything();
	while(1)
	{
		//setBG(0x07E0);
		//drawString("Thanks for playing!", 160, 120);
		//Font test below.
		/* drawString("0123456789", 0, 120);
		drawString("abcdefghijklmnopqrstuvwxyz", 0, 0);
		drawString("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 0, 200); */
		//while(1);
		Menu(); //Won't return until we select an option
		buttonPushed = 0;
		buttonPushedB = 0;
		loaded = 0;
		GameLoop(); //Upon return, print string. If dead, goes back to menu
	}
	//drawString("THANKS FOR PLAYING!", 0, 120);
}

#define YUp 		(sampleY > 0xC0F)
#define YDown		(sampleY < 0x640)
/* Functions to write */
void Menu()
{
	setBG(0xBE66); //Set to gold
	whiteBG();
	uint8_t menuSelect = 1; //0 is Start game, 1 is main menu screen, 2 is load game, 3 is settings
	uint8_t SelectionPos = 1; //Keeps track of where the cursor is.
	uint8_t SelectionPos2 = 1; //1 is english, 2 is spanish
	uint8_t language = 1; //1 is english, 2 is spanish
	menuX = 60;
	menuY = 90;
	while(menuSelect != 0)
	{
		if((menuSelect == 1) && (language == 1))
		{
			loadImage("Main Menu.bmp", 0, 0);
			do
			{
				sampleY = getJY(); //Grab sample to draw
				loadImage("Menu Arrow.bmp", menuX, menuY); //Load menu arrow
				delay1ms(20);
				#define S1X 60
				#define S1Y 90
				#define S2X 30
				#define S2Y 135
				#define S3X 40
				#define S3Y 185
				#define S4X 60
				#define S4Y	100
				#define S5X 60
				#define S5Y 150
				#define S6X	40
				#define S6Y 80
				#define S7X	10
				#define S7Y 135
				#define S8X	20
				#define S8Y 185
				if(SelectionPos == 1) //Hovering over start game
				{
					
					//If button pressed, start game
					checkPushA();
					if(buttonPushed == 1)
						menuSelect = 0;
					//If stick down, go to position 2
					if(YDown)
					{
						drawRect(S1X, S1Y, 56, 36, 0xFFFF); //Draw over the menu cursor
						menuX = S2X;
						menuY = S2Y;
						SelectionPos = 2;
					}
				}
				else if(SelectionPos == 2) //Hovering over Load game
				{
					
					//If button pressed, load the menu for loading from save file
					checkPushA();
					if(buttonPushed == 1)
					{
						buttonPushed = 0;
						loadGame();
						//If it returns back, load was unsucessful.
						//void drawGradientRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t Color)
						//void drawWindow(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
						if(loaded == 0)
						{
							drawWindow(47, 84, 250, 30);
							drawGradientRect(48, 85, 249, 30, 0x001F);
							drawString("File not found", 60, 90);
							delay1ms(500);
							while(buttonPushed != 1)
								checkPushA();
							buttonPushed = 0;
							loadImage("Main Menu.bmp", 0, 0);
						}
						else if(loaded == 1)
						{
							loadImage("Main Menu.bmp", 0, 0);
							//loadImage("Menu Arrow.bmp", S1X, S1Y);
							SelectionPos = 1;
							menuSelect = 1;
						}
					}
					//If stick up, go to first position
					if(YUp)
					{
						drawRect(S2X, S2Y, 56, 36, 0xFFFF);
						menuX = S1X;
						menuY = S1Y;
						SelectionPos = 1;
					}
					//If stick down, go to third position
					else if(YDown)
					{
						drawRect(S2X, S2Y, 56, 36, 0xFFFF);
						menuX = S3X;
						menuY = S3Y;
						SelectionPos = 3;
					}
				}
				else if(SelectionPos == 3) //Hovering over settings
				{
					//If button pressed, load the settings menu
					checkPushA();
					if(buttonPushed == 1){
						buttonPushed = 0;
						menuSelect = 3;
					}
					//If stick up, go to second position
					if(YUp)
					{
						drawRect(S3X, S3Y, 56, 36, 0xFFFF);
						menuX = S2X;
						menuY = S2Y;
						SelectionPos = 2;
					}
				}
			}while(menuSelect == 1);
		}

//spanish -----------------------------------------------------------------------------------
		if((menuSelect == 1) && (language == 2))
		{
			loadImage("Main Menu ESP.bmp", 0, 0);
			menuX = S8X;
			menuY = S8Y;
			do
			{
				sampleY = getJY(); //Grab sample to draw
				loadImage("Menu Arrow.bmp", menuX, menuY); //Load menu arrow
				delay1ms(20);
				
				if(SelectionPos == 1) //Hovering over start game
				{
					
					//If button pressed, start game
					checkPushA();
					if(buttonPushed == 1)
						menuSelect = 0;
					//If stick down, go to position 2
					if(YDown)
					{
						drawRect(S6X, S6Y, 56, 36, 0xFFFF); //Draw over the menu cursor
						menuX = S7X;
						menuY = S7Y;
						SelectionPos = 2;
					}
				}
				else if(SelectionPos == 2) //Hovering over Load game
				{
					
					//If button pressed, load the menu for loading from save file
					
					//If stick up, go to first position
					if(YUp)
					{
						drawRect(S7X, S7Y, 56, 36, 0xFFFF);
						menuX = S6X;
						menuY = S6Y;
						SelectionPos = 1;
					}
					//If stick down, go to third position
					else if(YDown)
					{
						drawRect(S7X, S7Y, 56, 36, 0xFFFF);
						menuX = S8X;
						menuY = S8Y;
						SelectionPos = 3;
					}
				}
				else if(SelectionPos == 3) //Hovering over settings
				{
					//If button pressed, load the settings menu
					checkPushA();
					if(buttonPushed == 1){
						buttonPushed = 0;
						menuSelect = 3;
					}
					//If stick up, go to second position
					if(YUp)
					{
						drawRect(S8X, S8Y, 56, 36, 0xFFFF);
						menuX = S7X;
						menuY = S7Y;
						SelectionPos = 2;
					}
				}
			}while(menuSelect == 1);
		}
//Load Game----------------------------------------------------------------------------------------
		else if(menuSelect == 2)
		{
			do
			{
				
			}while(menuSelect == 2);
		}
		
//settings-----------------------------------------------------------------------------------------
		else if(menuSelect == 3)
		{
			//replace following line with menu screen
			loadImage("Settings.bmp", 0, 0);
			menuX = S4X;
			menuY = S4Y;
			
			do
			{
				sampleY = getJY(); //Grab sample to draw
				loadImage("Menu Arrow.bmp", menuX, menuY); //Load menu arrow
				delay1ms(20);
				
			if(SelectionPos2 == 1) //Hovering over english
				{
					//If button pressed, start game
					checkPushA();
					if(buttonPushed == 1){
						language = 1;
						buttonPushed = 0;
					}
					//If stick down, go to position 2
					if(YDown)
					{
						drawRect(S4X, S4Y, 56, 36, 0xFFFF); //Draw over the menu cursor
						menuX = S5X;
						menuY = S5Y;
						SelectionPos2 = 2;
					}
				}
				else if(SelectionPos2 == 2) //Hovering over spanish
				{
					//If button pressed, change language to spanish
					checkPushA();
					if(buttonPushed == 1){
						language = 2;
						buttonPushed = 0;
					}	
					//If stick up, go to first position
					if(YUp)
					{
						drawRect(S5X, S5Y, 56, 36, 0xFFFF);
						menuX = S4X;
						menuY = S4Y;
						SelectionPos2 = 1;
					}
				}
				checkPushB();
				if(buttonPushedB == 1){
					menuSelect = 1;
					buttonPushedB = 0;
					drawRect(S5X, S5Y, 56, 36, 0xFFFF);
					drawRect(S4X, S4Y, 56, 36, 0xFFFF);
					SelectionPos = 3;
					if (language == 1){
						menuX = S3X;
						menuY = S3Y;
					}
					if(language == 2){
						menuX = S8X;
						menuY = S8Y;
					}
					
				}	
			}while(menuSelect == 3);
		}
	}
}

void checkPushA()
{
	if ((GPIO_PORTF_DATA_R & 0x10)== 0x00) 
	{
		playsound(daggerswishSound);
		buttonPushed = 1;
	}
	
}

void checkPushB()
{
	if ((GPIO_PORTF_DATA_R & 0x01)== 0x00) 
	{
		playsound(maceSound);
		buttonPushedB = 1;
	}
	
}
/* ASM Part of the file */

static void DInt()
{
	__asm
	{
		CPSID I
	}
}

static void EInt()
{
	__asm
	{
		CPSIE I
	}
}

static void delay1ms(uint32_t period)
{
	period--;
	do
	{
		uint16_t time = 6665;
		while(time--);
	}while(period--);
}
