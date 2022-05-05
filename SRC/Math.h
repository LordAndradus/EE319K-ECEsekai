#include "inc/TM4C123GH6PM.h"
#include <stdint.h>
#include <stdio.h>

//Unsigned
#define uint32Max 0xFFFFFFFF;
#define uint16Max	0xFFFF;
#define uint8Max	0xFF
//Signed
#define int32Max	0x7FFFFFFF
#define int32Min	0x10000000
#define int16Max	0x7FFF
#define int16Min	0x1000
#define int8Max		0x7F
#define	int8Min		0x10

void mathInit(void);

uint32_t Power(uint32_t x, uint32_t y);
uint32_t sqrt(uint32_t x);
uint32_t abs(int32_t x);

int32_t sum(int32_t *arr, uint32_t size);
int32_t sPower(int32_t x, int32_t y);
int32_t sRoot(int32_t x, int32_t y);
int32_t sin(int32_t x);
int32_t log(uint32_t base, uint32_t x);
int32_t matrixMult(int32_t *mat1, int32_t *mat2);

void randInit(void);
uint32_t rand(uint32_t min, uint32_t max);
uint32_t srand(uint32_t min, uint32_t max);
uint32_t intRand(void);
void Timer1AInit(void);
void NVICInit(void);

