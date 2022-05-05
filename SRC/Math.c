#include "inc/TM4C123GH6PM.h"
#include <stdint.h>
#include <stdio.h>
#include "Math.h"

static uint32_t result;
static int32_t sresult;

static void DInt();
static void EInt();

/* unsigned versions */
uint32_t Power(uint32_t x, uint32_t y) //Overflow? Set to max int value
{
	if(x == 1 || y == 1) return x; //Save processing time, just return a 1.
	if(x == 2) return x << y;
	result = x;
	while(y != 1 && y--) result *= x;
	if(result == 0) return uint32Max; //Return overflow value.
	return result;
}

uint32_t abs(int32_t x)
{
	return (x < 0) ? (x * -1): x;
}

uint32_t sqrt(uint32_t x)
{
	//f(x) = x^2 - n, where n is the root to find. as x^2 = n, and then x = sqrt(n)
	//f'(x) = 2x
	if(!x) return x; //x is zero, return zero
	uint32_t diff = uint32Max;
	uint32_t xn = x;	//xn
	uint32_t xn1 = xn1 = xn - ((xn * xn - x)/(2*xn));; //xn+1
	while(diff > 0) //Keeps going until accurate
	{
		xn1 = (xn - (xn * xn - x)/(2*xn));
		diff = xn1 - xn;
		xn = xn1;
	}
	return xn1 - 1; //return the floor
}

/* signed versions */
int32_t sPower(int32_t x, int32_t y)
{
	if(x == (1 | -1) || y == 1) return x;
	//If negative power, it's 1/x^y, but integers are kinda doo doo, so return a 0.
	else if(y < 0) return 0;
	sresult = x;
	while(y != 1 && y--)
	{
		sresult *= x;
	}
	return sresult;
}

int32_t sRoot(int32_t x, int32_t y) //Highly inaccurate with large numbers.
{
	//f(x) = x^f - n, where f is the root power and n is the number to find
	//f'(x) = fx^(f-1)
	if(x == 1) return 0;
	if(!x) return x;
	uint32_t diff = uint32Max;
	int32_t xn = x; //xn = n
	int32_t xn1 = xn - (((Power(xn, y) - x) / ((y) * Power(xn, y-1)))+1);
	while(diff > 0)
	{
		xn1 = xn - ((Power(xn, y) - x) / ((y) * Power(xn, y-1)));
		diff = xn1 - xn;
		xn = xn1;
	}
	xn1--; //Make it a floor.
	return xn1 = (y % 2 == 0) ? abs(xn1) : xn1;
}

int32_t sum(int32_t *arr, uint32_t size)
{
	int32_t sum = 0;
	uint32_t IDX = 0;
	while(IDX != size)
	{
		sum += arr[IDX];
		IDX++;
	}
	return sum;
}

int32_t log(uint32_t base, uint32_t x)
{
	return (x > base - 1) ? 1 + log(x / base, base) : 0; //Works kinda wonky, but I'm too lazy to think of a faster way
}

/* random functions */
//More predictable, but spits out a result in 1 iteration
uint32_t rand(uint32_t min, uint32_t max)
{
	if(min > max) (min ^= max), (max ^= min), (min ^= max); //bad call, swap.
	uint32_t range = max - min;
	uint32_t seed = TIMER1_TAR_R;
	uint32_t tempSeed;
	/* main calculations */
	seed = TIMER1_TAR_R;
	seed += seed * seed * max;
	seed <<= 16;
	tempSeed = TIMER1_TAR_R * TIMER1_TAR_R;
	tempSeed = (((tempSeed * 666) + 77777777)/4) % min;
	seed += (tempSeed & 0xFFFF); //Ensures we have a full 32-bit value to work with.
	seed %= (range + 1);
	seed += min;
	return seed;
}	

//less predictable, but uses more processing power and time
//srand == slow rand
uint32_t srand(uint32_t min, uint32_t max)
{
	uint32_t seed;
	uint32_t tempSeed;
	uint32_t sum = 0;
	do{
	seed = TIMER1_TAR_R; //Time as the seed
	seed += seed * seed * max;
	seed <<= 16;
	tempSeed = TIMER1_TAR_R;
	tempSeed = (((tempSeed * 67) + 16723489)/2) % min;
	seed += (tempSeed & 0xFFFF);
	seed %= (max + 1);
	sum += seed;
	if(sum > max) sum %= max; //bad sum, reset.
	}while(seed < min && sum < min); //Whatever comes first.
	return seed = (sum > min) ? sum : seed; //Return what matches min.
}

uint32_t intRand() //Just a random number. Very predictable.
{
	return (TIMER1_TAR_R * TIMER1_TAR_R) + TIMER1_TAR_R;
}

void randInit()
{
	DInt();
	//Init Timer1A
	Timer1AInit();
	//get first value
	EInt();
	rand(0, 100);
}

#define TClock SYSCTL_RCGCTIMER_R
void Timer1AInit()
{
	TClock |= 0x02; //Activate Timer1
	while((TClock & 0x02) == 0);
	TIMER1_CTL_R = 0; //Disable Timer for config
	TIMER1_CFG_R = 0; //Config to 32-bit mod
	TIMER1_TAMR_R = 2; //Periodic mode
	TIMER1_TAILR_R = 0xFFFFFFFE;
	TIMER1_TAPR_R = 0;
	TIMER1_ICR_R = 1;
	TIMER1_IMR_R = 1;
	NVIC_PRI5_R = (NVIC_PRI5_R&0xFFFF00FF) | 0x0000E000; //Priority level 7.
	
	NVIC_EN0_R = 1 << 21;
	TIMER1_CTL_R = 1;
}

void Timer1A_Handler(void)
{
	TIMER1_ICR_R = TIMER_ICR_TATOCINT; //Acknowledge timeout. Start over.
}

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

