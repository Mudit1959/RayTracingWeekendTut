#ifndef SPHERE_H
#define SPHERE_H

#include "common.h"
#include "hittable.h"


class sphere : public hittable 
{
public:

	sphere(const point3& c, double r) :center(c), radius(std::fmax(0, r)) {}

	bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override 
	{
		// Use the simplified x^2 + y^2 + z^2 = r^2 formula to find if a collision occured -> discriminant
		vec3 oc = center - r.origin();

		auto a = r.direction().length_squared();
		auto h = dot(r.direction(), oc);
		auto c = oc.length_squared() - (radius * radius);

		auto discriminant = (h * h) - (a * c);

		if (discriminant < 0) { return false; }

		auto sqrtd = std::sqrt(discriminant);

		//Check both roots for validity! -> Check for the object being in front or behind the camera
		auto root = (h - sqrtd) / a; // No 2*a due to simplification
		if (root <= ray_tmin || root >= ray_tmax) 
		{
			root = (h + sqrtd) / a;
			if (root <= ray_tmin || root >= ray_tmax) { return false; }
		}

		rec.t = root; // Scalar magnitude of ray's direction to reach sphere
		rec.p = r.at(rec.t); // Point of contact with sphere
		vec3 outward_normal = (rec.p - center) / radius; // The NORMALIZED surface normal -> The spot is on the outermost part of a sphere, where everything is a radius away from the center!
		rec.set_face_normal(r, outward_normal); // Flip normals if in the same direction as the ray 

		return true;
	}

private:
	point3 center;
	double radius;
};

#endif // !SPHERE_H
