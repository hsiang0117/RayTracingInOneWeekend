#ifndef UTILS_HPP
#define UTILS_HPP

#include<cmath>
#include<iostream>
#include<limits>
#include<memory>

using std::make_shared;
using std::shared_ptr;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
	return degrees * pi / 180.0;
}

#include "Color.hpp"
#include "Interval.hpp"
#include "Ray.hpp"
#include "Vec3.hpp"

#endif // !UTILS_HPP
