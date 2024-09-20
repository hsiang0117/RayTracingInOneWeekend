#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Hittable.hpp"

class camera {
public:
	void render() {

	}

private:
	double aspect_ratio = 16.0 / 9.0;
	int image_width = 400;

	double focal_length = 1.0;
	double viewport_height = 2.0;
	point3 center = point3(0, 0, 0);

	vec3 pixel_delta_u;
	vec3 pixel_delta_v;
	point3 pixel00_coord;

	void initialize() {
		auto image_height = image_width / aspect_ratio;
		auto viewport_width = viewport_height * (double(image_width) / image_height);

		auto viewport_u = vec3(viewport_width, 0, 0);
		auto viewport_v = vec3(0, -viewport_height, 0);

		pixel_delta_u = viewport_u / image_width;
		pixel_delta_v = viewport_v / image_height;

		auto viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
		pixel00_coord = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
	}

	color ray_color(const ray& r, const hittable& world)const {
		hit_record rec;
		interval ray_t(0, infinity);
		if (world.hit(r, ray_t, rec)) {
			return 0.5 * (rec.normal + color(1, 1, 1));
		}
		vec3 unit_direction = unit_vector(r.direction());
		auto a = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
	}


};

#endif // !CAMERA_HPP
