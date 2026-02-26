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

#endif
