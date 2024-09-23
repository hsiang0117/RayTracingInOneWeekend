#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Hittable.hpp"

class material {
public:
	virtual ~material() = default;
	virtual bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered)const {
		return false; 
	}
};

#endif // !MATERIAL_HPP
