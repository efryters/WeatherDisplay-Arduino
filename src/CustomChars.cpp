#include <Arduino.h>
#include "CustomChars.h"

byte solA[8] =
{
	0b00000,
	0b10101,
	0b01110,
	0b11011,
	0b01110,
	0b10101,
	0b00000,
	0b00000
};

byte solB[8] =
{
	0b10101,
	0b10101,
	0b01110,
	0b11011,
	0b01110,
	0b10101,
	0b10101,
	0b00000
};

byte overcastL[8] =
{
	0b00000,
	0b00010,
	0b01101,
	0b10000,
	0b10000,
	0b10010,
	0b01101,
	0b00000
};

byte overcastR[8] =
{
	0b00000,
	0b01000,
	0b10110,
	0b00001,
	0b00001,
	0b01001,
	0b10110,
	0b00000
};