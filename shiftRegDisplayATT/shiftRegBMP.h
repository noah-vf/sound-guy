#ifndef shiftRegBMP_h
#define shiftRegBMP_h
#include "Arduino.h"



byte bm_nums[10][8]{
	{
	0b00000000,
  0b00111110,
  0b01111111,
  0b01010001,
  0b01001001,
  0b01111111,
  0b00111110,
  0b00000000
},

{
  0b00000000,
  0b00000001,
  0b00000001,
  0b01111111,
  0b01111111,
  0b00010001,
  0b00000001,
  0b00000000
},

{
  0b00000000,
  0b00110001,
  0b01111001,
  0b01001001,
  0b01000101,
  0b01100111,
  0b00100011,
  0b00000000
},

{
  0b00000000,
  0b00110110,
  0b01111111,
  0b01001001,
  0b01001001,
  0b01100011,
  0b00100010,
  0b00000000
},
{
  0b00000000,
  0b00000100,
  0b01111111,
  0b01111111,
  0b00100100,
  0b00010100,
  0b00001100,
  0b00000000
},
{
  0b00000000,
  0b01001110,
  0b01011111,
  0b01010001,
  0b01010001,
  0b01110011,
  0b01110010,
  0b00000000
},
{
  0b00000000,
  0b00100110,
  0b01101111,
  0b01001001,
  0b01001001,
  0b01111111,
  0b00111110,
  0b00000000
},
{
  0b00000000,
  0b01100000,
  0b01111000,
  0b01011111,
  0b01000111,
  0b01100000,
  0b01100000,
  0b00000000
},
{
  0b00000000,
  0b00110110,
  0b01111111,
  0b01001001,
  0b01001001,
  0b01111111,
  0b00110110,
  0b00000000
},
{
  0b00000000,
  0b00111110,
  0b01111111,
  0b01001001,
  0b01001001,
  0b01111011,
  0b00110010,
  0b00000000
}};


byte bm_uparrow[8] = {
      0b00010000,
      0b00110000,
      0b01111111,
      0b11111111,
      0b01111111,
      0b00110000,
      0b00010000,
      0b00000000
    };
byte bm_downarrow[8] = {
      0b00000000,  
      0b00010000,
      0b00110000,
      0b01111111,
      0b11111111,
      0b01111111,
      0b00110000,
      0b00010000
};

byte bm_note[8] = {
  0b01111100,
  0b01001110,
  0b01000110,
  0b01100000,
  0b00111110,
  0b00000111,
  0b00000011,
  0b00000000
};


#endif
