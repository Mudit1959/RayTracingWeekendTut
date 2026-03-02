
#ifndef HITTABLE_H
#define HITTABLE_H

#include "common.h"

class material;

// To keep track of where a hit occured, the normal at the point of contact, and the scalar multiplier of ray direction to reach that point
class hit_record 
{
public:
	point3 p; // Where is the spot on the object surface?
	vec3 normal; // What is the surface normal?
	shared_ptr<material> mat; // What is the object made of?
	double t; // Scalar magnitude of ray to surface
	bool front_face; //Is the face on the outside of the object?

	void set_face_normal(const ray& r, const vec3& outward_normal) 
	{
		// To always have the normal emerging opposite the incoming light ray
		front_face = dot(r.direction(), outward_normal) < 0; // If negative, they already oppose each other, but if in the same direction...
		normal = front_face ? outward_normal : -outward_normal; // Reverse the normal
	}
};

// Abstract class for objects rays of light can collide with
class hittable 
{
public:

	virtual ~hittable() = default; //???? -> Default constructor?

	virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif