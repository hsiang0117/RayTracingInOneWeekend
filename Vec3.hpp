#ifndef VEC3_HPP
#define VEC3_HPP

class vec3 {
public:
	double e[3];

	vec3() :e{ 0,0,0 } {};
	vec3(double e0, double e1, double e2) :e{ e0,e1,e2 } {};

	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }

	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	double operator[](int i) const { return e[i]; }
	double& operator[](int i) { return e[i]; }

	vec3& operator+=(const vec3& v) {
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	vec3& operator*=(const double t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	vec3& operator /= (const double t) {
		return *this *= 1 / t;
	}

	double length() const {
		return std::sqrt(length_squared());
	}

	double length_squared() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	static vec3 random() {
		return vec3(random_double(), random_double(),random_double());
	}

	static vec3 random(double min, double max) {
		return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
	}
};

using point3 = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(const vec3& v, const double t) {
	return vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}

inline vec3 operator*(const double t, const vec3& v) {
	return v * t;
}

inline vec3 operator/(const vec3& v, const double t) {
	return v * (1 / t);
}

inline double dot(const vec3& u, const vec3& v) {
	return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& v, const vec3& u) {
	return vec3(
		u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[1] * v.e[3] - u.e[3] * v.e[1],
		u.e[2] * v.e[3] - u.e[3] * v.e[2]
	);
}

inline vec3 unit_vector(const vec3& v) {
	return v / v.length();
}

inline vec3 random_unit_vector() {
	while (true) {
		auto random_vector = vec3::random(-1, 1);
		if (1e-160 < random_vector.length_squared() && random_vector.length_squared() <= 1) {
			return random_vector / sqrt(random_vector.length_squared());
		}
	}
}

inline vec3 random_on_hemisphere(const vec3& normal) {
	vec3 unit_vector = random_unit_vector();
	if (dot(unit_vector, normal) > 0.0) {
		return unit_vector;
	}
	else {
		return -unit_vector;
	}
}

#endif // !VEC3_HPP
