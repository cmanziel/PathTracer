#pragma once

#include <stdint.h>

class rgb
{
public:
	rgb();
	// default argumetn a = 255: full opacity of a pixel
	rgb(uint8_t rc, uint8_t gc, uint8_t bc, uint8_t ac = 255);

	rgb& operator=(const rgb& other);

	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};

