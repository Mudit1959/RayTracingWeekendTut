#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream> // to handle printing methods

class vec3 // a vector3 contains 3 doubles
{
public:

	double f[3]; // just an array of 3 doubles underneath

	vec3() :f{ 0,0,0 } {} // initializes the array to 0

	vec3(double f1, double f2, double f3) :f{ f1, f2, f3 } {}

	double x() const { return f[0]; } // ? - Why is const added in the function signature
	double y() const { return f[1]; }
	double z() const { return f[2]; }

	vec3 operator-() const { return vec3(-f[0], -f[1], -f[2]); } // Negate the vector
	double operator[](int i) const { return f[i]; } // one element
	double& operator[](int i) { return f[i]; } // one element

	// - ! - datatype& -> Pass by reference 
	// - Any changes in the function are reflected back in the original variables
	vec3& operator+=(const vec3& v) // Add another vector to it
	{
		f[0] += v.f[0];
		f[1] += v.f[1];
		f[2] += v.f[2];

		return *this;
	}

	vec3& operator*=(double m)
	{
		f[0] *= m;
		f[1] *= m;
		f[2] *= m;

		return *this;
	}

	vec3& operator/=(double m)
	{
		return *this *= (1.0f / m);
	}

	double length() const { return std::sqrt(length_squared()); }

	double length_squared() const { return f[0] * f[0] + f[1] * f[1] + f[2] * f[2]; }

	static vec3 random() 
	{
		return vec3(random_double(), random_double(), random_double());
	}

	static vec3 random(double min, double max)
	{
		return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
	}

	bool near_zero() const // To check if vector is close to 0,0,0 
	{
		auto s = 1e-8;
		return ((std::fabs(f[0]) < s) && (std::fabs(f[1]) < s) && (std::fabs(f[2]) < s));
	}
	
};

using point3 = vec3; // Another way to refer to the same data (vec3)

inline std::ostream& operator<<(std::ostream& out, const vec3& v)
{
	return out << v[0] << ' ' << v[1] << v[2];
}

inline vec3 operator+(const vec3& u, const vec3& v)
{
	return vec3(u.f[0] + v.f[0], u.f[1] + v.f[1], u.f[2] + v.f[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v)
{
	return vec3(u.f[0] - v.f[0], u.f[1] - v.f[1], u.f[2] - v.f[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v)
{
	return vec3(u.f[0] * v.f[0], u.f[1] * v.f[1], u.f[2] * v.f[2]);
}

inline vec3 operator*(double t, const vec3& v)
{
	return vec3(t * v.f[0], t * v.f[1], t * v.f[2]);
}

inline vec3 operator*(const vec3& v, double t)
{
	return t * v;
}

inline vec3 operator/(const vec3& v, double t)
{
	return (1.0f / t) * v;
}

inline double dot(const vec3& u, const vec3& v)
{
	return (u[0] * v[0]) + (u[1] * v[1]) + (u[2] * v[2]);
}

inline vec3 cross(const vec3& u, const vec3& v)
{
	return vec3(u[1] * v[2] - u[2] * v[1],
		u[2] * v[0] - u[0] * v[2],
		u[0] * v[1] - u[1] * v[0]);
}

inline vec3 unit_vector(const vec3& v)
{
	return v / v.length();
}

inline vec3 random_unit_vector()
{
	while (true)
	{
		vec3 p = vec3::random(-1, 1);
		float length_sq = p.length_squared();
		if (1e-160 < length_sq && length_sq <= 1) 
		{
			return p / sqrt(length_sq);
		}
	}
}

inline vec3 random_vec_on_hemisphere(const vec3& normal)
{
	vec3 in_sphere = random_unit_vector();
	if(dot(in_sphere, normal) < 0.0)
	{
		return -in_sphere;
	}
	//else
	return in_sphere;
}

inline vec3 reflect(const vec3& v, const vec3& normal) 
{
	return v - (2 * dot(v, normal) * normal);
}

inline vec3 refract(const vec3& uv, const vec3& n, double etai_by_etat) 
{
	float cos_theta = std::fmin(dot(-uv, n), 1.0); // The incident ray and normal have been normalized before this
	vec3 r_out_perp = etai_by_etat * (uv + cos_theta * n); // perpendicular
	vec3 r_out_para = -std::sqrt(std::fabs(1-r_out_perp.length_squared())) * n;
	return r_out_perp + r_out_para;
}


inline vec3 random_in_unit_disk() {
	while (true) {
		auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
		if (p.length_squared() < 1)
			return p;
	}
}

#endif
