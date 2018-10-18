#include "Pixel.h"

Pixel::Pixel()
	{
	_color = ColorDbl{ 1.0, 1.0, 1.0 };
	_r = 1.0;
	_g = 1.0;
	_b = 1.0;
	}
Pixel::Pixel(ColorDbl &color) 
	:_color{color} 
{
	_r = color._r;
	_g = color._g;
	_b = color._b;
}