#ifndef SPHERE_HPP
#define SPHERE_HPP

#include"Hittable.hpp"

class sphere :public hittable {
public:
	sphere(const point3& center, double radius) :center(center), radius(std::fmax(0,radius)) {}
	bool hit(const ray& r, interval ray_t, hit_record& rec)const override {
		vec3 oc = this->center - r.origin();
		auto a = dot(r.direction(), r.direction());
		auto half_b = dot(r.direction(), oc);
		auto c = oc.length_squared() - radius * radius;
		auto discriminant = half_b * half_b - a * c;
		if (discriminant < 0)return false;
		auto root = (half_b - sqrt(discriminant)) / a;
		if (!ray_t.contains(root)) {
			root = (half_b + sqrt(discriminant)) / a;
			if (!ray_t.contains(root)) {
				return false;
			}
		}
		
		rec.p = r.at(root);
		rec.t = root;
		vec3 outward_normal = (r.at(root) - this->center) / radius;
		rec.set_face_normal(r, outward_normal);

		return true;
	}
private:
	point3 center;
	double radius;
};

#endif // !SPHERE_HPP
