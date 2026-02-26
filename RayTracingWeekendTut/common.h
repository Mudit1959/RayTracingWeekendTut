#ifndef COMMON_H
#define COMMON_H

#include <cmath>
#include <iostream>
#include <limits>
#include "vector"

using std::make_shared;
using std::shared_ptr;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) 
{
	return degrees * pi / 180.0;
}

// Common header files
#include "color.h"
#include "ray.h"
#include "vec3.h"

#endif
