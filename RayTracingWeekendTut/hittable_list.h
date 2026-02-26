#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "common.h"
#include "hittable.h"

// To store all "hittable" objects - objects that light rays can collide with

class hittable_list : public hittable 
{
	public:
		std::vector<shared_ptr<hittable>> objects;

		hittable_list() {}
		hittable_list(shared_ptr<hittable> obj) { add(obj); }

		void clear() { objects.clear(); }

		void add(shared_ptr<hittable> obj) { objects.push_back(obj); }

		// To check if light hit any of the objects
		bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override 
		{
			hit_record check; // To hold details of the closest object to the camera
			bool anything_yet = false; // Have any objects been hit by light rays emerging from the camera?
			auto closest_yet = ray_tmax; // Max scalar magnitude along ray's direction to reach closest object

			for (const auto& o : objects) 
			{
				if (o->hit(r, ray_tmin, closest_yet, check)) 
				{
					anything_yet = true; // We hit!
					closest_yet = check.t; // magnitude
					rec = check; // reassign 
				}
			}

			return anything_yet;
		}
};

#endif
