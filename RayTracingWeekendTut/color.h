#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "interval.h"
#include <iostream>

using color = vec3;

inline double apply_gamma(double value)
{
	if (value > 0) 
	{
		return pow(value, 1.0/2.2);
	}
}

void write_color(std::ostream& out, const color& pixel_color) 
{
	// RGB stored in 0-1 range
	auto r = apply_gamma(pixel_color.x());
	auto g = apply_gamma(pixel_color.y());
	auto b = apply_gamma(pixel_color.z());

	// Map RGB to 0-255 range
	static const interval intensity(0.000, 0.999);
	int rbyte = int(256 * intensity.clamp(r));
	int gbyte = int(256 * intensity.clamp(g));
	int bbyte = int(256 * intensity.clamp(b));

	// Write out R G B
	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif
