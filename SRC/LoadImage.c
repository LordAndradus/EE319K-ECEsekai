#include <stdint.h>
#include "SDCard.h"
#include "LCD.h"

extern uint8_t SPC;
uint8_t IMGBuffer[1024];

void loadTile(const uint16_t *IMG, uint16_t x, uint16_t y)
{
	uint16_t index = 0;
	uint8_t XPos = 0; uint8_t YPos = 0;
	setAddr(x, y, x + 39, y + 39);
	do
	{
		drawPixel(x + XPos, y + YPos, IMG[index]);
		XPos++;
		if(XPos > 39)
		{
			YPos++;
			XPos = 0;
		}
		index++;
	}while(index < 1599);
}

void loadImage(uint8_t *name, uint16_t x, uint16_t y) //Loads a 16-bit bitmap from SDCard, Top-Botoom, and with a quantization factor of 8
{ //Max image size: 319 by 239, if it's even 1 pixel to long, it'll mess up, gauranteed.
	selectLCD;
	uint32_t Cluster = FileByName(name);
	uint32_t oldCluster = Cluster;
	uint8_t IMGsector = 0;
	readFromFile(IMGBuffer, 1, Cluster, IMGsector); //Get image size, so we know when to stop printing IMGBuffer
	uint16_t Yaxis = y;
	uint16_t FPY = 0; //Floating point check
	uint16_t width = (((uint16_t) IMGBuffer[0x12]) + (((uint16_t) IMGBuffer[0x13]) << 8)); //Get width information, since our screen max is 480 width wise, we only need a 2 byte value
	uint16_t height = ((uint16_t) ~(((uint32_t) IMGBuffer[0x16]) + (((uint32_t) IMGBuffer[0x17]) << 8) + (((uint32_t) IMGBuffer[0x18]) << 16) + (((uint32_t) IMGBuffer[0x19]) << 24))) + 1;
	uint8_t padding = 0;
	if(width % 2)
		padding += 2; //Since there are only 2 bytes per line, that would mean an odd #'d width for a BMP would have 2 bytes of padding.
	uint16_t offset = (((uint16_t) IMGBuffer[0x0A]) + (((uint16_t) IMGBuffer[0x0B]) << 8));
	setAddr(x, y, x + width - 1, y + height - 1); //Set window area to manipulate
	//Start drawing the bitmap.
	do
	{
		Cluster = readFromFile(IMGBuffer, 2, Cluster, IMGsector);
		if(oldCluster != Cluster)
		{
			oldCluster = Cluster;
			IMGsector = 0;
			Cluster = readFromFile(IMGBuffer, 2, Cluster, IMGsector);
		}
		IMGsector += 2;
		IMGsector %= SPC + 1;
		drawBitmap(&IMGBuffer[offset], x, Yaxis, width, height, padding, offset); //Implements command 0x3C, to continue where you leave off of.
		
		Yaxis += (1024 / (width * 2));	//Increment by how many times the width was drawn in the drawBitmap function
		FPY += (1024 % (width * 2));
		if(FPY > 640)
		{
			Yaxis++;
			FPY -= 640;
		}
		
		offset = 0; //Get rid of offset, it has served its asinine purpose.
	}while(Yaxis < y + (height - 1));
	deselectLCD;
}

int32_t size;
void loadTransparentImage(uint8_t *name, uint16_t x, uint16_t y) //Loads a bitmap with the white pixel (0xFFFF) skipped, however those can be supplemented with 0xFFFE if you so wish to have white colors.
{		
	selectLCD;
	uint32_t Cluster = FileByName(name);
	size = sizeFromFile(name); //Size in bytes
	uint32_t oldCluster = Cluster;
	uint8_t IMGsector = 0;
	readFromFile(IMGBuffer, 1, Cluster, IMGsector); //Get image size, so we know when to stop printing IMGBuffer
	uint16_t Yaxis = y;
	uint16_t FPY = 0; //Floating point check
	uint16_t width = (((uint16_t) IMGBuffer[0x12]) + (((uint16_t) IMGBuffer[0x13]) << 8)); //Get width information, since our screen max is 480 width wise, we only need a 2 byte value
	uint16_t height = ((uint16_t) ~(((uint32_t) IMGBuffer[0x16]) + (((uint32_t) IMGBuffer[0x17]) << 8) + (((uint32_t) IMGBuffer[0x18]) << 16) + (((uint32_t) IMGBuffer[0x19]) << 24))) + 1;
	uint8_t padding = 0;
	if(width % 2)
		padding += 2; //Since there are only 2 bytes per line, that would mean an odd #'d width for a BMP would have 2 bytes of padding.
	uint16_t offset = (((uint16_t) IMGBuffer[0x0A]) + (((uint16_t) IMGBuffer[0x0B]) << 8));
	size -= (offset * 2);
	setAddr(x, y, x + width - 1, y + height - 1); //Set window area to manipulate
	do
	{
		Cluster = readFromFile(IMGBuffer, 2, Cluster, IMGsector);
		if(oldCluster != Cluster)
		{
			oldCluster = Cluster;
			IMGsector = 0;
			Cluster = readFromFile(IMGBuffer, 2, Cluster, IMGsector);
		}
		IMGsector += 2;
		IMGsector %= SPC + 1;
		drawTransparentBitmap(&IMGBuffer[offset], x, Yaxis, width, height, padding, offset); //Implements command 0x3C, to continue where you leave off of.
		
		Yaxis += (1024 / (width * 2));	//Increment by how many times the width was drawn in the drawBitmap function
		FPY += (1024 % (width * 2));
		if(IMGsector == 2) Yaxis--; //Temp fix, but not good for images larger than 1 cluster, lines are... Segmented???
		if(FPY > 1024) //Floating point is over the limit, add it to the Y-axis
		{
			Yaxis++;
			FPY -= 1024;
		}
		
		offset = 0; //Get rid of offset, it has served its asinine purpose.
	}while(size > 0);
	deselectLCD;
}


//An array that is a pointer towards an array that contains letters. 
const uint16_t *LetNumAcc[] =
{
	//Numbers
	(uint16_t *) Num0, (uint16_t *) Num1, (uint16_t *) Num2, (uint16_t *) Num3, (uint16_t *) Num4, (uint16_t *) Num5, (uint16_t *) Num6, (uint16_t *) Num7, (uint16_t *) Num8, (uint16_t *) Num9,
	
	//UpperCase
	(uint16_t *) A, (uint16_t *) B, (uint16_t *) C, (uint16_t *) D, (uint16_t *) E, (uint16_t *) F, (uint16_t *) G, (uint16_t *) H, (uint16_t *) I, (uint16_t *) J, (uint16_t *) K, (uint16_t *) L, 
	(uint16_t *) M, (uint16_t *) N, (uint16_t *) O, (uint16_t *) P, (uint16_t *) Q, (uint16_t *) R, (uint16_t *) S, (uint16_t *) T, (uint16_t *) U, (uint16_t *) V, (uint16_t *) W, (uint16_t *) X, 
	(uint16_t *) Y, (uint16_t *) Z,
	
	//Lowercase
	(uint16_t *) IMGa, (uint16_t *) IMGb, (uint16_t *) IMGc, (uint16_t *) IMGd, (uint16_t *) IMGe, (uint16_t *) IMGf, (uint16_t *) IMGg, (uint16_t *) IMGh, (uint16_t *) IMGi, (uint16_t *) IMGj,
	(uint16_t *) IMGk, (uint16_t *) IMGl, (uint16_t *) IMGm, (uint16_t *) IMGn, (uint16_t *) IMGo, (uint16_t *) IMGp, (uint16_t *) IMGq, (uint16_t *) IMGr, (uint16_t *) IMGs, (uint16_t *) IMGt,
	(uint16_t *) IMGu, (uint16_t *) IMGv, (uint16_t *) IMGw, (uint16_t *) IMGx, (uint16_t *) IMGy, (uint16_t *) IMGz,
	
	//Modifiers (! , etc) - Debating on doing this
	
	
	//Accented letters - Special detection, '(Letter) + (Normal)
	(uint16_t *) AccA, (uint16_t *) AccE, (uint16_t *) AccI, (uint16_t *) AccO, (uint16_t *) AccU, (uint16_t *) AccU2, (uint16_t *) AccN
};

void drawChar(unsigned char CHAR, uint16_t x, uint16_t y) //Draw a character from ROM. Unusual convention, but for accented letters, you have to specify the index they're located at
{
	//If calling "A", then the ASCII is 101, whereby that's the offset to finding the letter in Character[] array
	uint8_t XPos = 0; //Goes up to 11, increments y and resets to 0
	uint8_t YPos = 0; //Supposed to only go up by 15
	#define NumOff		48
	#define UCCharOff 55 //Uppercase offset - 65 - 10 = 55
	#define LCCharOff 61 //Lowercase offset - (97 - (10 + 26)) = 61
	uint16_t *PTR;
	//Ignore warnings, they're just dumb.
	if(CHAR >= 0x41 && CHAR <= 0x5A) //It's an uppercase letter
		(const uint16_t *) PTR = LetNumAcc[CHAR - UCCharOff];
	else if(CHAR >= 0x61 && CHAR <= 0x7A) //It's a Lowercase letter
		(const uint16_t *) PTR = LetNumAcc[CHAR - LCCharOff];
	else if(CHAR >= 0x30 && CHAR <= 0x39) 		//It's a number
		(const uint16_t *) PTR = LetNumAcc[CHAR - NumOff];
	else if(CHAR == 160)
		(const uint16_t *) PTR = LetNumAcc[62];
	else if(CHAR == 130)
		(const uint16_t *) PTR = LetNumAcc[63];
	else if(CHAR == 161)
		(const uint16_t *) PTR = LetNumAcc[64];
	else if(CHAR == 162)
		(const uint16_t *) PTR = LetNumAcc[65];
	else if(CHAR == 163)
		(const uint16_t *) PTR = LetNumAcc[66];
	else if(CHAR == 164)
		(const uint16_t *) PTR = LetNumAcc[67];
	else if(CHAR == 129)
		(const uint16_t *) PTR = LetNumAcc[66];
	else if(CHAR == '!') //Exclmation point
		(const uint16_t *) PTR = LetNumAcc[10];
	else if(CHAR == '?') //Question mark
		(const uint16_t *) PTR = LetNumAcc[10];
	else if(CHAR == '.') //Period
		(const uint16_t *) PTR = LetNumAcc[10];
	else if(CHAR == ',') //Comma
		(const uint16_t *) PTR = LetNumAcc[10];
	/*else if(CHAR blah //It's a special accented character
	*/
	//Special character have a very weird index... So, use the index if you want these. As for when we draw a string, detect if it's 'A and such
	uint8_t i = 0;
	do
	{
		if(PTR[i] != 0xFFFF) 
		{
			drawPixel(x + XPos, y + YPos, 0x0000);
		}
		//Find next pixel
		i++;
		XPos++;
		
		if(XPos > 11) //Increment Y if going out of X bounds
		{
			YPos++;
			XPos = 0;
		}
	}while(YPos < 16);
}

void drawString(unsigned char *String, uint16_t x, uint16_t y)
{
	uint16_t oldX = x;
	uint8_t index = 0;
	do
	{
		if(String[index] == 0x20) //Spaces are skipped
		{
			x += 15;
			index++;
		}
		//Check out of bounds
		if(305 - x < 0 && String[index] != 96) //Character is outbounds. 305 because 320 - 15 = 305, will add a dash or a trianglular arrow point right for continuation
		{
			y += 20; x = oldX;
			drawChar(String[index], x, y);
			x += 15;
			index++;
		}
		//Check accented characters
		if(String[index] == 96) //Acented character detected
		{
			if(305 - x < 0) //Make sure it won't go out of bounds
			{
				y += 20; x = oldX;
			}
			switch(String[index + 1])
			{
				case 0:
					break;
				default:
					break;
			}
			index += 2;
			x += 15;
		}
		//Check special modifiers
		
		//Draw normal character
		drawChar(String[index], x, y);
		x += 15; //15 Pixel spacing between characters
		index++;
	}while(String[index] != 0); //Zero terminated string, of course
}

void toString(uint32_t data, uint16_t x, uint16_t y)
{
	if(data == 0)
		drawChar('0', x, y);
		
	uint8_t STR[5] = {0, 0, 0, 0, 0}; //10 character limit
	uint8_t IDX = 4;
	uint8_t CNT = 0;
	uint8_t digit;
	do
	{
		digit = data % 10;
		data = data / 10;
		STR[IDX] = digit;
		IDX--;
		CNT++;
	}while(data != 0 && IDX != 0);
	//Shift index to the left until first index is not zero
	IDX = 0;
	while(STR[0] == 0)
	{
		for(int i = 0; i < 5; i++)
		{
			STR[i] = STR[i + 1];
		}
	}
	//Draw chars based on how many digits we got
	CNT--;
	do
	{
		drawChar(STR[IDX] + 0x30, x, y);
		IDX++;
		x += 15;
	}while(CNT--);
}
