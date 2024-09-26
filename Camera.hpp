#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Material.hpp"

class camera {
public:
	double aspect_ratio = 16.0 / 9.0;
	int image_width = 400;
	int samples_per_pixel = 100;
	int max_depth = 50;
	double vfov = 90;

	double focus_angle = 0;
	double focus_distance = 10;

	point3 center = point3(0, 0, 0);
	vec3 lookat = vec3(0, 0, -1);
	vec3 up = vec3(0, 1, 0);

	camera(){}
	camera(double aspect_ratio, double image_width, double vfov) :aspect_ratio(aspect_ratio), image_width(image_width), vfov(vfov) {}

	void render(const hittable& world) {
		initialize();

		std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

		for (int j = 0; j < image_height; j++) {
			std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
			for (int i = 0; i < image_width; i++) {
				color pixel_color(0, 0, 0);
				for (int sample = 0; sample < samples_per_pixel; sample++) {
					ray r = get_ray(i, j);
					pixel_color += ray_color(r, max_depth, world);
				}
				write_color(std::cout, pixel_color * pixel_samples_scale);
			}
		}
		std::clog << "\rDone" << std::endl;
	}


private:
	int image_height;
	double pixel_samples_scale;

	vec3 pixel_delta_u;
	vec3 pixel_delta_v;
	point3 pixel00_coord;

	vec3 focus_disk_u;
	vec3 focus_disk_v;

	void initialize() {
		image_height = image_width / aspect_ratio;
        image_height = (image_height < 1) ? 1 : image_height;
		pixel_samples_scale = 1.0 / samples_per_pixel;

		auto theta = degrees_to_radians(vfov);
		auto h = std::tan(theta / 2.0);
		auto viewport_height = 2 * h * focus_distance;
		auto viewport_width = viewport_height * (double(image_width) / image_height);

		auto w = unit_vector(lookat - center);
		auto u = unit_vector(cross(w, up));
		auto v = cross(u, w);
		auto viewport_u = u * viewport_width;
		auto viewport_v = -v * viewport_height;

		pixel_delta_u = viewport_u / image_width;
		pixel_delta_v = viewport_v / image_height;

		auto viewport_upper_left = center + (focus_distance * w) - viewport_u / 2 - viewport_v / 2;
		pixel00_coord = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

		auto focus_radius = focus_distance * std::tan(degrees_to_radians(focus_angle / 2.0));
		focus_disk_u = u * focus_radius;
		focus_disk_v = v * focus_disk_v;
	}

	color ray_color(const ray& r, int depth, const hittable& world) const {
		if (depth <= 0) return color(0, 0, 0);
		hit_record rec;
		interval ray_t(0.001, infinity);
		if (world.hit(r, ray_t, rec)) {
			color attenuation;
			ray scattered;
			if (rec.mat->scatter(r, rec, attenuation, scattered)) {
				return attenuation * ray_color(scattered, depth - 1, world);
			}
			return color(0, 0, 0);
		}
		vec3 unit_direction = unit_vector(r.direction());
		auto a = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
	}

	ray get_ray(int i, int j)const {
		auto offset = sample_square();
		auto pixel_sample = pixel00_coord
			+ ((i + offset.x()) * pixel_delta_u)
			+ ((j + offset.y()) * pixel_delta_v);
		auto ray_origin = focus_angle <= 0 ? center : get_sample_from_disk();
		auto ray_direction = pixel_sample - ray_origin;

		return ray(ray_origin, ray_direction);
	}

	vec3 sample_square() const {
		return vec3(random_double() - 0.5, random_double() - 0.5, 0);
	}

	point3 get_sample_from_disk() const {
		auto p = random_in_unit_disk();
		return center + p.x() * focus_disk_u + p.y() * focus_disk_v;
	}
};

#endif // !CAMERA_HPP
