#include <stdint.h>
#include "SDCard.h"
#include "LCD.h"

void loadTile(const uint16_t *IMG, uint16_t x, uint16_t y); //Load a tile from ROM
void loadImage(uint8_t *name, uint16_t x, uint16_t y); //Load a 16-bit BMP from top to bottom through an SD Card medium
void loadTransparentImage(uint8_t *name, uint16_t x, uint16_t y);
void drawChar(unsigned char CHAR, uint16_t x, uint16_t y);
void drawString(unsigned char *String, uint16_t x, uint16_t y);
void toString(uint32_t data, uint16_t x, uint16_t y);


#ifndef TILE
#define TILE
//Map 1 tile
static const uint16_t TILE1[1600] = {
    0x2925, 0x2104, 0x20e4, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 0x20e4, 0x20e4, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x18c3, 0x20e4, 0x20e4, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2925, 0x20e4, 0x20e4, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 
    0x2925, 0x2924, 0x2924, 0x2104, 0x2104, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 0x20e4, 0x2104, 0x2924, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x18c3, 0x2904, 0x2924, 0x2104, 0x2104, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2925, 0x2924, 0x2924, 0x2104, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 
    0x2925, 0x2925, 0x2925, 0x2924, 0x2104, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x18c3, 0x2924, 0x2925, 0x2924, 0x2104, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2925, 0x2925, 0x2925, 0x2924, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 
    0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x18c3, 0x2924, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 
    0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 0x2924, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 
    0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x18c3, 0x2924, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x3165, 0x2104, 0x18c3, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 
    0x2925, 0x2925, 0x2945, 0x3166, 0x3165, 0x3165, 0x3166, 0x2945, 0x2104, 0x18c3, 0x2945, 0x2945, 0x2924, 0x2924, 0x2924, 0x2924, 0x2925, 0x2925, 0x2924, 0x20e4, 0x2925, 0x2925, 0x2924, 0x2924, 0x2924, 0x2924, 0x3166, 0x2104, 0x20e3, 0x3166, 0x3165, 0x3165, 0x3165, 0x3165, 0x3165, 0x3165, 0x3165, 0x3166, 0x2945, 0x18c3, 
    0x2104, 0x2104, 0x2924, 0x2925, 0x2925, 0x2925, 0x2945, 0x2925, 0x20e4, 0x18c3, 0x3166, 0x3165, 0x2945, 0x2945, 0x2945, 0x2945, 0x2945, 0x2925, 0x2924, 0x20e4, 0x2925, 0x2945, 0x2945, 0x2945, 0x2945, 0x2945, 0x3186, 0x2124, 0x18c3, 0x2945, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2945, 0x2104, 0x18a3, 
    0x2104, 0x2104, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e3, 0x20e3, 0x20c3, 0x18c3, 0x2945, 0x2945, 0x2945, 0x2945, 0x2945, 0x2945, 0x2925, 0x2924, 0x2104, 0x20e4, 0x2904, 0x2945, 0x2945, 0x2945, 0x2945, 0x2945, 0x2945, 0x2104, 0x18c3, 0x20e3, 0x20e4, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x20e4, 0x20e4, 0x20e4, 0x20e3, 
    0x2925, 0x2925, 0x2104, 0x20e4, 0x20e4, 0x2104, 0x18c3, 0x18c3, 0x18c3, 0x18c3, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x18c3, 0x18c3, 0x18c3, 0x18c3, 0x2924, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2925, 0x2925, 
    0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 0x2925, 0x20e3, 0x20e4, 0x2925, 0x2924, 0x2924, 0x2925, 0x2104, 0x20e4, 0x20e4, 0x20e4, 0x2924, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2925, 0x2925, 0x2104, 0x2104, 0x2924, 0x20e4, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2924, 0x2104, 0x2104, 0x2925, 
    0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x2925, 0x18c3, 0x20e4, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x2924, 0x2924, 0x20e4, 0x2924, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2925, 0x2925, 0x2104, 0x2104, 0x2924, 0x20e4, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 0x2924, 0x2925, 0x2924, 0x2925, 
    0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x18c3, 0x20e4, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2924, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2925, 0x2104, 0x2104, 0x2924, 0x2924, 0x20e4, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2924, 0x2925, 0x2925, 
    0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x20e3, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2925, 0x2104, 0x2924, 0x2925, 0x2924, 0x20e4, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2925, 0x2925, 
    0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 
    0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 
    0x2925, 0x2925, 0x2925, 0x2924, 0x2924, 0x2925, 0x2104, 0x2924, 0x2945, 0x2924, 0x2924, 0x2924, 0x2924, 0x2924, 0x2924, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x20e3, 0x2925, 0x2924, 0x2924, 0x2925, 0x2924, 0x20e4, 0x2924, 0x2925, 0x2924, 0x2924, 0x2924, 0x2924, 0x2924, 0x2925, 0x2925, 0x2925, 
    0x2925, 0x2925, 0x2945, 0x2945, 0x2945, 0x3165, 0x2104, 0x2925, 0x3186, 0x2945, 0x2945, 0x2945, 0x2945, 0x2945, 0x2945, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e3, 0x20e3, 0x3165, 0x2945, 0x2945, 0x3165, 0x2925, 0x20e4, 0x2945, 0x2945, 0x2945, 0x2945, 0x2945, 0x2945, 0x2945, 0x2945, 0x2925, 0x2925, 
    0x2924, 0x2904, 0x2925, 0x2945, 0x2945, 0x2945, 0x20e4, 0x2104, 0x2945, 0x2945, 0x2945, 0x2945, 0x2945, 0x2945, 0x2945, 0x2924, 0x2924, 0x2924, 0x2924, 0x2924, 0x2104, 0x20e4, 0x18c3, 0x20e3, 0x2945, 0x2945, 0x2945, 0x3145, 0x2925, 0x20e4, 0x2945, 0x2945, 0x2945, 0x2945, 0x2945, 0x2945, 0x2945, 0x2925, 0x2924, 0x2924, 
    0x20e4, 0x20e4, 0x20e4, 0x20e3, 0x18c3, 0x18c3, 0x18c3, 0x18c3, 0x18c3, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x18c3, 0x18c3, 0x18c3, 0x18c3, 0x18c3, 0x18c3, 0x20e3, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 
    0x2925, 0x2925, 0x2104, 0x20e4, 0x20e4, 0x2924, 0x2924, 0x2924, 0x2924, 0x2925, 0x2925, 0x2104, 0x20e4, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 0x20e4, 0x2904, 0x2925, 0x2924, 0x2924, 0x2924, 0x2924, 0x2925, 0x2925, 0x2925, 0x2924, 0x2925, 0x2104, 0x2104, 0x2925, 0x2925, 0x2924, 0x2925, 0x2924, 0x20e4, 
    0x2925, 0x2925, 0x2925, 0x2104, 0x20e4, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2924, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 0x2924, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 
    0x2925, 0x2925, 0x2925, 0x2924, 0x2104, 0x2104, 0x2924, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 0x2925, 0x2925, 0x2925, 0x2924, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 
    0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2924, 0x2925, 0x2925, 0x2925, 0x2945, 0x2104, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 
    0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x3166, 0x2104, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 0x2924, 0x2925, 0x2925, 0x2924, 0x2104, 0x2924, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 
    0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x2925, 0x3166, 0x20e4, 0x20e4, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 0x2924, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 0x2924, 0x2925, 0x2925, 0x2925, 0x2925, 0x3165, 0x2925, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 
    0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2945, 0x3166, 0x3166, 0x3186, 0x20e3, 0x20e4, 0x2945, 0x2925, 0x2925, 0x2925, 0x2945, 0x2104, 0x18c3, 0x2945, 0x2945, 0x2924, 0x2925, 0x2925, 0x2924, 0x2924, 0x2925, 0x2924, 0x2924, 0x2924, 0x3165, 0x2924, 0x20e3, 0x2925, 0x2924, 0x2924, 0x2945, 0x2945, 0x20e4, 
    0x2104, 0x2104, 0x2104, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x2104, 0x2924, 0x2924, 0x2104, 0x20e3, 0x20e4, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x20e3, 0x18c3, 0x3166, 0x3165, 0x2945, 0x2925, 0x2925, 0x2925, 0x2945, 0x2945, 0x2945, 0x2945, 0x2945, 0x3186, 0x2104, 0x18c3, 0x2945, 0x2945, 0x2945, 0x3166, 0x3165, 0x20e4, 
    0x2104, 0x2104, 0x20e4, 0x18c3, 0x18c3, 0x18c3, 0x18c3, 0x18c3, 0x18a3, 0x18c3, 0x18c3, 0x2104, 0x2104, 0x2104, 0x2104, 0x20e4, 0x20e4, 0x20e3, 0x18c3, 0x18c3, 0x2945, 0x3145, 0x2925, 0x2904, 0x2924, 0x2924, 0x2945, 0x2945, 0x2945, 0x2945, 0x2945, 0x2945, 0x2104, 0x18c3, 0x2104, 0x2945, 0x2945, 0x2945, 0x2925, 0x20e4, 
    0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x20e3, 0x18c3, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x2104, 0x20e4, 0x2924, 0x2924, 0x18c3, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x18c3, 0x18c3, 0x18c3, 0x18c3, 0x18c3, 0x18c3, 0x20e3, 0x20e4, 0x20e4, 0x20e4, 
    0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x20e4, 0x20e4, 0x2104, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 0x2924, 0x2925, 0x2925, 0x2925, 0x2924, 0x2924, 0x2924, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2925, 0x2924, 0x20e4, 0x20e3, 0x2104, 0x2925, 0x2924, 0x2924, 0x2924, 0x2925, 0x2925, 0x2925, 
    0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2924, 0x2104, 0x20e4, 0x2925, 0x2925, 0x2925, 0x2924, 0x2924, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2925, 0x2925, 0x2924, 0x2924, 0x2104, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 
    0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2924, 0x2925, 0x2924, 0x20e4, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 
    0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 
    0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 
    0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x20e4, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2104, 0x2104, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 
    0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x2924, 0x2924, 0x2945, 0x2945, 0x18c3, 0x2924, 0x2925, 0x2924, 0x2924, 0x2924, 0x2924, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2924, 0x2925, 0x20e3, 0x2104, 0x3165, 0x2924, 0x2924, 0x2924, 0x2924, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 
    0x2925, 0x2925, 0x2925, 0x2945, 0x3165, 0x2945, 0x2945, 0x3166, 0x2945, 0x18c3, 0x2945, 0x2965, 0x2945, 0x2945, 0x2945, 0x2945, 0x2945, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2945, 0x3165, 0x3165, 0x20e3, 0x2104, 0x3186, 0x2945, 0x2945, 0x2945, 0x3165, 0x2945, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 0x2925, 
    0x2924, 0x2924, 0x2924, 0x2924, 0x2945, 0x2945, 0x2945, 0x2945, 0x2924, 0x18c3, 0x2945, 0x3145, 0x2945, 0x2945, 0x2945, 0x2945, 0x2925, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2924, 0x2945, 0x2945, 0x20e3, 0x2104, 0x3165, 0x2945, 0x2945, 0x2945, 0x2945, 0x2925, 0x2104, 0x2104, 0x2104, 0x2904, 0x2924, 0x2924, 
    0x20e4, 0x20e4, 0x20e4, 0x20e3, 0x18c3, 0x18c3, 0x18c3, 0x18c3, 0x18c3, 0x18c3, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e4, 0x20e3, 0x18c3, 0x18c3, 0x18c3, 0x18c3, 0x18c3, 0x18c3, 0x18c3, 0x18c3, 0x18c3, 0x20e3, 0x20e4, 0x20e4, 0x20e4, 0x18c3, 0x18c3, 0x18c3, 0x18c3, 0x18c3, 0x18c3, 0x20e3, 0x20e4, 0x20e4
};

static const uint16_t TILE2[1600] = {
    0x2145, 0x2124, 0x1924, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2124, 0x2124, 0x2144, 0x2145, 0x2145, 0x2145, 0x2145, 0x2165, 0x2124, 0x18e3, 0x1924, 0x2124, 0x2144, 0x2165, 0x2145, 0x2145, 0x2165, 0x1924, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x1903, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 
    0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2124, 0x2144, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2165, 0x2124, 0x18e3, 0x2145, 0x2145, 0x2124, 0x2124, 0x2145, 0x2145, 0x2165, 0x1924, 0x18e3, 0x1904, 0x1904, 0x1904, 0x1924, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 
    0x2145, 0x2145, 0x2165, 0x2145, 0x2144, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2144, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2165, 0x2124, 0x18e3, 0x2145, 0x2165, 0x2145, 0x2144, 0x2145, 0x2145, 0x2165, 0x1924, 0x18e3, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 
    0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2165, 0x2144, 0x1903, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2165, 0x1924, 0x1903, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 
    0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2165, 0x2144, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 
    0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2986, 0x2965, 0x1924, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 
    0x2145, 0x2145, 0x2965, 0x2986, 0x2986, 0x2986, 0x2986, 0x2986, 0x2145, 0x2124, 0x2986, 0x2165, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2986, 0x2965, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x18e3, 
    0x2144, 0x2124, 0x2145, 0x2965, 0x2965, 0x2965, 0x2965, 0x2145, 0x2124, 0x2124, 0x31a6, 0x2986, 0x2986, 0x2986, 0x2986, 0x2986, 0x2165, 0x2165, 0x2145, 0x2124, 0x2145, 0x2966, 0x2986, 0x2986, 0x2986, 0x2986, 0x31a6, 0x2965, 0x1924, 0x2145, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2145, 0x2124, 0x18e3, 
    0x2124, 0x2124, 0x2124, 0x1924, 0x1924, 0x1924, 0x1924, 0x1924, 0x1924, 0x2124, 0x2965, 0x2986, 0x2986, 0x2986, 0x2965, 0x2965, 0x2145, 0x2145, 0x2144, 0x2124, 0x2145, 0x2965, 0x2986, 0x2986, 0x2986, 0x2986, 0x2986, 0x2145, 0x1924, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x1904, 
    0x2145, 0x2165, 0x2144, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x1924, 0x1924, 0x2124, 0x1904, 0x18e3, 0x18e3, 0x18e3, 0x1903, 0x2124, 0x2124, 0x2124, 0x2124, 0x1924, 0x1924, 0x2124, 0x2124, 0x1924, 0x2124, 0x2124, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2144, 0x2145, 0x2165, 
    0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2145, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x1904, 0x18e3, 0x18e3, 0x1924, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2145, 0x2145, 0x2124, 0x2144, 0x2145, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2145, 0x2144, 0x2124, 0x2145, 
    0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x1903, 0x18e3, 0x18e3, 0x1924, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2145, 0x2165, 0x2124, 0x2144, 0x2145, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 
    0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2124, 0x2124, 0x2124, 0x1903, 0x1903, 0x1903, 0x1904, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2145, 0x2144, 0x2144, 0x2145, 0x2145, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2144, 0x2124, 0x2145, 0x2165, 0x2145, 
    0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2124, 0x2124, 0x2124, 0x18e3, 0x1924, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2145, 0x2124, 0x2145, 0x2165, 0x2145, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2165, 0x2124, 0x2144, 0x2145, 0x2145, 
    0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 
    0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2145, 0x2144, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 
    0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2145, 0x2145, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 
    0x2145, 0x2145, 0x2165, 0x2986, 0x2986, 0x2986, 0x2144, 0x1924, 0x2124, 0x2124, 0x2124, 0x2144, 0x2145, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2145, 0x2145, 0x2144, 0x2124, 0x2144, 0x2986, 0x2986, 0x2986, 0x2986, 0x2165, 0x2124, 0x2986, 0x2986, 0x2986, 0x2986, 0x2986, 0x2986, 0x2986, 0x2165, 0x2145, 0x2145, 
    0x2145, 0x2145, 0x2165, 0x2986, 0x2986, 0x2986, 0x2144, 0x1924, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x1924, 0x2144, 0x2986, 0x2986, 0x2986, 0x2986, 0x2965, 0x2124, 0x2985, 0x2986, 0x2986, 0x2986, 0x2986, 0x2986, 0x2986, 0x2165, 0x2145, 0x2145, 
    0x2124, 0x2124, 0x2124, 0x1924, 0x1924, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x1924, 0x1924, 0x1924, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x1924, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 
    0x2145, 0x2145, 0x2144, 0x1924, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x1903, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x1903, 0x2124, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 
    0x2145, 0x2145, 0x2145, 0x2144, 0x2124, 0x2145, 0x2165, 0x2145, 0x2145, 0x2145, 0x2145, 0x2144, 0x1903, 0x18e3, 0x18e3, 0x1904, 0x1904, 0x1904, 0x1904, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2165, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2165, 0x2144, 0x2124, 0x2145, 0x2145, 0x2145, 0x2165, 0x2145, 0x2124, 
    0x2145, 0x2145, 0x2145, 0x2145, 0x2144, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x1924, 0x1903, 0x1903, 0x1904, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2144, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2144, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 
    0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2165, 0x1904, 0x1903, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 
    0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2165, 0x31a6, 0x1924, 0x1903, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2165, 0x2144, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 
    0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x29a6, 0x1904, 0x1903, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2986, 0x2965, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 
    0x2145, 0x2145, 0x2165, 0x2165, 0x2165, 0x2165, 0x2145, 0x2986, 0x29a6, 0x29a6, 0x31a6, 0x2144, 0x1904, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2986, 0x2165, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2986, 0x2145, 0x1904, 0x2145, 0x2145, 0x2145, 0x2965, 0x2965, 0x2124, 
    0x2144, 0x2144, 0x2124, 0x1904, 0x1924, 0x1924, 0x1924, 0x2124, 0x2145, 0x2145, 0x2144, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x1924, 0x2124, 0x31a6, 0x2986, 0x2165, 0x2145, 0x2145, 0x2165, 0x2965, 0x2986, 0x2986, 0x2986, 0x2986, 0x31a6, 0x2145, 0x18e3, 0x2165, 0x2986, 0x2986, 0x29a6, 0x2986, 0x1924, 
    0x2124, 0x2124, 0x1904, 0x1903, 0x1903, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2965, 0x2986, 0x2165, 0x2145, 0x2145, 0x2145, 0x2965, 0x2986, 0x2986, 0x2986, 0x2965, 0x2965, 0x2124, 0x18e3, 0x2145, 0x2965, 0x2986, 0x2986, 0x2965, 0x2124, 
    0x2145, 0x2145, 0x2145, 0x2165, 0x2145, 0x2124, 0x2124, 0x1903, 0x18e3, 0x2124, 0x2145, 0x2165, 0x2145, 0x2145, 0x2145, 0x2124, 0x2124, 0x2145, 0x2145, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x1924, 0x1924, 0x1904, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x1904, 0x2124, 0x2124, 0x2124, 
    0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x1924, 0x1924, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x1903, 0x18e3, 0x18e3, 0x18e3, 0x1904, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 
    0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2145, 0x2145, 0x2144, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2165, 0x1904, 0x18e3, 0x18e3, 0x1904, 0x1904, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 
    0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2144, 0x2145, 0x2165, 0x2145, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2165, 0x1903, 0x18e3, 0x1904, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 
    0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x1904, 0x1904, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 
    0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 
    0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 
    0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2965, 0x2965, 0x1903, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x1904, 0x1924, 0x2145, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 
    0x2145, 0x2145, 0x2145, 0x2165, 0x2986, 0x2986, 0x2986, 0x29a6, 0x2965, 0x18e3, 0x2965, 0x2986, 0x2986, 0x2986, 0x2986, 0x2986, 0x2165, 0x2145, 0x2165, 0x2165, 0x2165, 0x2165, 0x2145, 0x2165, 0x2986, 0x2986, 0x1904, 0x1924, 0x2165, 0x2144, 0x2144, 0x2145, 0x2145, 0x2144, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 
    0x2145, 0x2145, 0x2145, 0x2145, 0x2965, 0x2965, 0x2965, 0x2985, 0x2145, 0x18e3, 0x2985, 0x2986, 0x2986, 0x2986, 0x2986, 0x2986, 0x2145, 0x2145, 0x2144, 0x2144, 0x2144, 0x2144, 0x2124, 0x2145, 0x2965, 0x2985, 0x1904, 0x1904, 0x2145, 0x2145, 0x2145, 0x2145, 0x2145, 0x2124, 0x1904, 0x1904, 0x1904, 0x1924, 0x2124, 0x2124, 
    0x2124, 0x2124, 0x2124, 0x1904, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x1924, 0x2124, 0x1924, 0x1924, 0x1924, 0x1924, 0x2124, 0x1903, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x1903, 0x2124, 0x2124, 0x2124, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x1903, 0x2124, 0x2124
};

static const uint16_t TILE3[1600] = {
    0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x18e3, 0x2124, 0x2144, 0x2144, 0x2144, 
    0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x2104, 0x2124, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2104, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x18e3, 0x2124, 0x2144, 0x2144, 0x2144, 
    0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x1903, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2104, 0x2144, 0x2964, 0x2964, 0x2964, 0x2964, 0x2964, 0x2964, 0x2964, 0x2964, 0x1903, 0x2124, 0x2144, 0x2144, 0x2144, 
    0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x2144, 0x2964, 0x2164, 0x2164, 0x2164, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2103, 0x2144, 0x2964, 0x2944, 0x2944, 0x2964, 0x2964, 0x2964, 0x2964, 0x2964, 0x2124, 0x2144, 0x2144, 0x2144, 0x2144, 
    0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x2144, 0x2965, 0x2965, 0x2965, 0x2965, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x2103, 0x2103, 0x2103, 0x2103, 0x2103, 0x2104, 0x2144, 0x2144, 0x2144, 0x2144, 
    0x18e3, 0x18e3, 0x18e3, 0x1903, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x18e3, 0x18e3, 0x18e3, 0x1903, 0x2124, 0x2124, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2103, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x2104, 0x2144, 0x2144, 0x2144, 0x2144, 
    0x2103, 0x2103, 0x2103, 0x1903, 0x1903, 0x1903, 0x1903, 0x1903, 0x1903, 0x1903, 0x18e3, 0x1903, 0x1903, 0x2103, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2124, 0x2103, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x2104, 0x2124, 0x2124, 0x2124, 0x2124, 
    0x2124, 0x2124, 0x2124, 0x2124, 0x2103, 0x2103, 0x18e3, 0x1903, 0x2123, 0x2103, 0x2123, 0x2124, 0x2124, 0x2124, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2124, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x1903, 0x2104, 0x2124, 0x2124, 0x2124, 0x2104, 
    0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2164, 0x1903, 0x2123, 0x2164, 0x2144, 0x2144, 0x2144, 0x2124, 0x2124, 0x2164, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2124, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x2124, 0x2124, 0x2144, 0x2144, 0x2144, 0x2104, 
    0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2124, 0x2124, 0x2144, 0x2144, 0x2144, 0x2144, 0x2124, 0x2124, 0x2965, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2164, 0x2965, 0x2124, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x2124, 0x2144, 0x2144, 0x2144, 0x2144, 0x2104, 
    0x2124, 0x1903, 0x18e3, 0x1903, 0x2104, 0x2104, 0x2104, 0x2124, 0x2144, 0x2144, 0x2144, 0x2144, 0x2103, 0x2103, 0x2985, 0x2965, 0x2965, 0x2965, 0x2965, 0x2965, 0x2144, 0x2144, 0x2964, 0x2985, 0x2965, 0x18e3, 0x2124, 0x2123, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x2124, 0x2144, 0x2144, 0x2144, 0x2144, 0x2104, 
    0x18e3, 0x18e3, 0x2103, 0x2144, 0x2144, 0x2144, 0x2124, 0x2104, 0x2124, 0x2144, 0x2144, 0x2164, 0x2123, 0x18e3, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2103, 0x2103, 0x18e3, 0x1903, 0x2124, 0x2144, 0x2144, 0x2144, 0x1903, 0x18e3, 0x2103, 0x2104, 0x2124, 0x2124, 0x2103, 0x18e3, 0x18e3, 
    0x2123, 0x18e3, 0x2123, 0x2164, 0x2144, 0x2144, 0x2144, 0x2124, 0x2104, 0x2124, 0x2124, 0x2124, 0x1903, 0x18e3, 0x18e3, 0x2103, 0x2103, 0x2103, 0x2103, 0x1903, 0x1903, 0x1903, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x1903, 0x2123, 0x2123, 0x2124, 0x2103, 0x2103, 0x2104, 0x2104, 0x2104, 0x2124, 0x2124, 0x2103, 0x2123, 
    0x2144, 0x1903, 0x2123, 0x2144, 0x2144, 0x2144, 0x2144, 0x2124, 0x2104, 0x2124, 0x2124, 0x1903, 0x1903, 0x1903, 0x1903, 0x2124, 0x2124, 0x2124, 0x2103, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x1903, 0x1903, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2144, 0x2144, 0x2144, 0x2144, 
    0x2144, 0x2124, 0x2124, 0x2144, 0x2144, 0x2144, 0x2144, 0x2124, 0x2124, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2124, 0x2103, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x2123, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 
    0x2144, 0x2124, 0x2124, 0x2144, 0x2144, 0x2144, 0x2144, 0x2124, 0x2124, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2124, 0x2103, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x2123, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 
    0x2144, 0x2124, 0x2144, 0x2964, 0x2144, 0x2144, 0x2144, 0x2124, 0x2124, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2124, 0x2103, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x2124, 0x2103, 0x2124, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 
    0x2144, 0x2124, 0x2144, 0x2985, 0x2964, 0x2964, 0x2164, 0x2124, 0x2124, 0x2964, 0x2964, 0x2964, 0x2964, 0x2964, 0x2144, 0x2144, 0x2144, 0x2124, 0x2103, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x2124, 0x2144, 0x2124, 0x2124, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 
    0x2144, 0x2124, 0x2124, 0x2964, 0x2964, 0x2964, 0x2144, 0x2124, 0x2124, 0x2964, 0x2964, 0x2964, 0x2964, 0x2144, 0x2144, 0x2144, 0x2144, 0x2124, 0x2103, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x2103, 0x2144, 0x2144, 0x2124, 0x2124, 0x2164, 0x2164, 0x2164, 0x2164, 0x2164, 0x2164, 0x2164, 0x2164, 0x2164, 0x2144, 0x2144, 0x2144, 
    0x2144, 0x2124, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2124, 0x2124, 0x2124, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2103, 0x2144, 0x2965, 0x2965, 0x2965, 0x2965, 0x2965, 0x2965, 0x2965, 0x2965, 0x2965, 0x2964, 0x2144, 0x2144, 
    0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2124, 0x1903, 0x18e3, 0x18e3, 0x2104, 0x2104, 0x2104, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 
    0x2144, 0x2144, 0x2144, 0x2124, 0x2104, 0x2104, 0x2124, 0x2144, 0x2144, 0x2144, 0x2104, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2103, 0x18e3, 0x2124, 0x2144, 0x2144, 0x2144, 0x2144, 0x2124, 0x2104, 0x2104, 0x2104, 0x2103, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 
    0x2144, 0x2144, 0x2144, 0x2144, 0x2124, 0x2104, 0x2144, 0x2144, 0x2144, 0x2144, 0x1903, 0x2144, 0x2964, 0x2964, 0x2964, 0x2964, 0x2964, 0x2164, 0x2144, 0x2144, 0x2144, 0x2164, 0x2123, 0x1903, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2124, 0x1903, 0x1903, 0x1903, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 
    0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2104, 0x2144, 0x2144, 0x2144, 0x2144, 0x18e3, 0x2124, 0x2964, 0x2944, 0x2944, 0x2964, 0x2965, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2103, 0x2103, 0x2164, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2103, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 
    0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2104, 0x2144, 0x2144, 0x2144, 0x2144, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x2103, 0x2103, 0x2103, 0x2104, 0x2104, 0x2104, 0x2104, 0x2103, 0x2124, 0x2965, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 
    0x2144, 0x2144, 0x2144, 0x2144, 0x2965, 0x2104, 0x2144, 0x2144, 0x2144, 0x2144, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x2104, 0x2104, 0x2103, 0x2124, 0x2985, 0x2965, 0x2985, 0x2964, 0x2144, 0x2144, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x2124, 0x2123, 0x18e3, 0x18e3, 
    0x2144, 0x2144, 0x2964, 0x2985, 0x2965, 0x2104, 0x2944, 0x2964, 0x2144, 0x2144, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x2104, 0x2104, 0x2104, 0x2104, 0x2124, 0x2103, 0x2103, 0x2103, 0x1903, 0x1903, 0x18e3, 0x18e3, 0x18e3, 0x1903, 0x2144, 0x2144, 0x2103, 0x18e3, 0x18e3, 0x18e3, 
    0x2124, 0x2124, 0x2124, 0x2144, 0x2144, 0x2104, 0x2124, 0x2124, 0x2103, 0x2123, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x2104, 0x2124, 0x2124, 0x2124, 0x2124, 0x2103, 0x2103, 0x1903, 0x18e3, 0x2123, 0x2123, 0x2123, 0x2103, 0x2103, 0x2124, 0x2124, 0x2103, 0x18e3, 0x1903, 0x1903, 
    0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2103, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x2104, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2164, 0x2123, 0x1903, 0x2144, 0x2144, 0x2144, 0x2144, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2104, 
    0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2124, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x2104, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2103, 0x1903, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2104, 
    0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2124, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x2104, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2124, 0x2124, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2104, 
    0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2124, 0x18e3, 0x2124, 0x2144, 0x2144, 0x2124, 0x2124, 0x2124, 0x2144, 0x2103, 0x18e3, 0x18e3, 0x2104, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2124, 0x2124, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2104, 
    0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2164, 0x2144, 0x18e3, 0x2123, 0x2123, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2104, 0x18e3, 0x1903, 0x2104, 0x2144, 0x2964, 0x2964, 0x2964, 0x2964, 0x2964, 0x2144, 0x2124, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2124, 0x2103, 0x2104, 
    0x2144, 0x2144, 0x2144, 0x2164, 0x2164, 0x2164, 0x2144, 0x2965, 0x2964, 0x18e3, 0x18e3, 0x18e3, 0x2103, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2104, 0x2144, 0x2964, 0x2964, 0x2964, 0x2964, 0x2965, 0x2124, 0x2104, 0x2144, 0x2144, 0x2144, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2103, 0x18e3, 0x2104, 
    0x2144, 0x2144, 0x2964, 0x2965, 0x2965, 0x2965, 0x2965, 0x2965, 0x2144, 0x18e3, 0x2104, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2124, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2124, 0x1903, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x1903, 0x2124, 0x2104, 
    0x2104, 0x2104, 0x2104, 0x2124, 0x2124, 0x2124, 0x1903, 0x18e3, 0x18e3, 0x18e3, 0x2104, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2104, 0x2124, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x18e3, 0x1903, 0x2104, 0x2104, 0x2104, 
    0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2124, 0x2124, 0x2124, 0x2124, 0x2104, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2104, 0x2964, 0x2985, 0x2965, 0x2965, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x18e3, 0x2103, 0x2103, 0x18e3, 0x18e3, 
    0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2104, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2104, 0x2124, 0x2144, 0x2144, 0x2144, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x18e3, 0x1903, 0x18e3, 0x18e3, 0x18e3, 
    0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2104, 0x2144, 0x2164, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2104, 0x2104, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x2124, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 
    0x2144, 0x2144, 0x2144, 0x2144, 0x2965, 0x2965, 0x2965, 0x2985, 0x2965, 0x2144, 0x2104, 0x2964, 0x2985, 0x2965, 0x2965, 0x2965, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2104, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x2144, 0x18e3, 0x18e3, 0x18e3, 0x18e3, 0x18e3
};
#endif