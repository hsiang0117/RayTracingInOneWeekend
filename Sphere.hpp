#ifndef SPHERE_HPP
#define SPHERE_HPP

#include"Hittable.hpp"

class sphere :public hittable {
public:
	sphere(point3& center, double radius) :center(center), radius(std::fmax(0,radius)) {}
	bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec)const override {
		vec3 oc = this->center - r.origin();
		auto a = dot(r.direction(), r.direction());
		auto half_b = dot(r.direction(), oc);
		auto c = oc.length_squared() - radius * radius;
		auto discriminant = half_b * half_b - a * c;
		if (discriminant < 0)return false;
		auto root = (half_b - sqrt(discriminant)) / a;
		if (root <= ray_tmin || root >= ray_tmax) {
			root = (half_b + sqrt(discriminant)) / a;
			if (root <= ray_tmin || root >= ray_tmax) {
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
