#include "rgb.h"

// intialize to black if no arguments are passed
rgb::rgb() : r(0), g(0), b(0), a(255) {}

rgb::rgb(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	: r(r), g(g), b(b), a(a)
{

}

rgb& rgb::operator=(const rgb& other)
{
	if (this == &other)
		return *this;

	this->r = other.r;
	this->g = other.g;
	this->b = other.b;

	return *this;
}