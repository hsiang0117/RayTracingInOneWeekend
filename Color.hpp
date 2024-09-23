#ifndef COLOR_HPP
#define COLOR_HPP

#include "Interval.hpp"
#include "Vec3.hpp"

using color = vec3;

inline double linear_to_gamma(const double x) {
	return x > 0 ? sqrt(x) : 0;
}

void write_color(std::ostream& out, const color& pixel_color) {
	static const interval rgb_interval(0.000, 0.999);
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	r = linear_to_gamma(r);
	g = linear_to_gamma(g);
	b = linear_to_gamma(b);

	int ir = int(256 * rgb_interval.clamp(r));
	int ig = int(256 * rgb_interval.clamp(g));
	int ib = int(256 * rgb_interval.clamp(b));

	out << ir << ' ' << ig << ' ' << ib << '\n';
}

#endif // !COLOR_HPP
