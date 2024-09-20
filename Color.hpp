#ifndef COLOR_HPP
#define COLOR_HPP

#include "Interval.hpp"
#include "Vec3.hpp"

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color) {
	static const interval rgb_interval(0.000, 0.999);
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	r = rgb_interval.clamp(r);
	g = rgb_interval.clamp(g);
	b = rgb_interval.clamp(b);

	int ir = int(256 * r);
	int ig = int(256 * g);
	int ib = int(256 * b);

	out << ir << ' ' << ig << ' ' << ib << '\n';
}

#endif // !COLOR_HPP
