#include "Pixel.h"

Pixel::Pixel()
	{
	_color = ColorDbl{ 1.0, 1.0, 1.0 };
	}
Pixel::Pixel(ColorDbl &color) 
	:_color{color} {}