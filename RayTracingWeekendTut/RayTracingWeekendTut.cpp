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
	/*
	// Make materials
	auto mat_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
	auto mat_red_metal = make_shared<metal>(color(1.0, 0, 0), 0);
	auto mat_blue_lambert = make_shared<lambertian>(color(0.1, 0.2, 0.5));
	auto mat_light_metal = make_shared<metal>(color(0.8, 0.8, 0.8), 1.0);
	auto mat_air_in_glass = make_shared<dielectric>(1.00 / 1.5);
	auto mat_glass = make_shared<dielectric>(1.5);

	// Define objects in world
	
	existing_objects.add(make_shared<sphere>(point3(0, 0, 1), 0.5, mat_blue_lambert));
	existing_objects.add(make_shared<sphere>(point3(0, -100.5, 1), 100, mat_ground));
	existing_objects.add(make_shared<sphere>(point3(-1, 0, 1), 0.5, mat_glass));
	existing_objects.add(make_shared<sphere>(point3(-1, 0, 1), 0.4, mat_air_in_glass));
	existing_objects.add(make_shared<sphere>(point3(1, 0, 1), 0.5, mat_red_metal));
	*/
    hittable_list existing_objects;

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    existing_objects.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    for (int a = -8; a < 8; a++) {
        for (int b = -8; b < 8; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    existing_objects.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    existing_objects.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    existing_objects.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    existing_objects.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    existing_objects.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    existing_objects.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));
	
	camera camera;
	

	camera.aspectRatio = 16.00 / 9.0;
	camera.vfov = 20;
	camera.screen_Width = 400;
	camera.samples_per_pixel = 50;
	camera.max_depth = 10;

	camera.world_pos = point3(13, 2, -3);
	camera.look_at = point3(0, 0, 0);
	camera.v_up = vec3(0, 1, 0);

	camera.defocus_angle = 0.6;
	camera.focus_dist = 10;

	camera.render(existing_objects);


}

// out\build\x64-debug\RayTracingWeekendTut.exe > image.ppm