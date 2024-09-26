#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Hittable.hpp"

class material {
public:
	virtual ~material() = default;
	virtual bool scatter(
		const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered
	)const {
		return false;
	}
};

class lambertian :public material {
public:
	lambertian(const color& albedo) :albedo(albedo) {}

	bool scatter(
		const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered
	)const override{
		auto scatter_direction = rec.normal + random_unit_vector();
		if (scatter_direction.near_zero()) {
			scatter_direction = rec.normal;
		}
		scattered = ray(rec.p, scatter_direction);
		attenuation = albedo;
		return true;
	}
private:
	color albedo;
};

class metal :public material {
public:
	metal(const color& albedo, const double fuzziness) :albedo(albedo), fuzziness(fuzziness < 1.0 ? fuzziness : 1.0) {}

	bool scatter(
		const ray& ray_in, const hit_record& rec, color& attenuation, ray& reflected
	)const override{
		auto reflect_direction = reflect(ray_in.direction(), rec.normal);
		reflect_direction = unit_vector(reflect_direction) + (fuzziness * random_unit_vector());
		reflected = ray(rec.p, reflect_direction);
		attenuation = albedo;
		return dot(reflect_direction, rec.normal) > 0;
	}
private:
	color albedo;
	double fuzziness;
};

class dielectric :public material {
public:
	dielectric(double refraction_index) :refraction_index(refraction_index) {}

	bool scatter(
		const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered
	)const override {
		attenuation = color(1, 1, 1);
		double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;
		vec3 unit_direction = unit_vector(ray_in.direction());
		double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
		double sin_theta = std::sqrt(1.0 - pow(cos_theta, 2));
		if (ri * sin_theta > 1.0 || reflectance(cos_theta, ri) > random_double()) {
			scattered = ray(rec.p, reflect(unit_direction, rec.normal));
		}
		else {
			scattered = ray(rec.p, refract(unit_direction, rec.normal, ri));
		}
		return true;
	}
private:
	double refraction_index;

	static double reflectance(double cosine, double refraction_index) {
		//采用Schlick近似计算菲涅尔方程
		auto r0 = (1 - refraction_index) / (1 + refraction_index);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}
};

#endif // !MATERIAL_HPP
