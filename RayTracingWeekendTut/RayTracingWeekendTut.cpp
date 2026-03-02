// RayTracingWeekendTut.cpp : Defines the entry point for the application.
//

#include "RayTracingWeekendTut.h"
#include "common.h"

#include "hittable.h"
#include "Sphere.h"
#include "hittable_list.h"
#include "camera.h"

using namespace std;


int main()
{
	// Make materials
	auto mat_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
	auto mat_red_metal = make_shared<metal>(color(1.0, 0, 0));
	auto mat_blue_lambert = make_shared<lambertian>(color(0.1, 0.2, 0.5));
	auto mat_light_metal = make_shared<metal>(color(0.8, 0.8, 0.8));

	// Define objects in world
	hittable_list existing_objects;
	existing_objects.add(make_shared<sphere>(point3(0, 0, 1), 0.5, mat_blue_lambert));
	existing_objects.add(make_shared<sphere>(point3(0, -100.5, 1), 100, mat_ground));
	existing_objects.add(make_shared<sphere>(point3(-1, 0, 1), 0.5, mat_light_metal));
	existing_objects.add(make_shared<sphere>(point3(1, 0, 1), 0.5, mat_red_metal));

	
	
	camera camera;
	camera.aspectRatio = 16.00 / 9.0;
	camera.screen_Width = 400;
	camera.samples_per_pixel = 10;
	camera.max_depth = 10;

	camera.render(existing_objects);


}
