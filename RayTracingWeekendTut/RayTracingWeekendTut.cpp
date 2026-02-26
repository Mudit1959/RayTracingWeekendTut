// RayTracingWeekendTut.cpp : Defines the entry point for the application.
//

#include "RayTracingWeekendTut.h"
#include "common.h"

#include "hittable.h"
#include "Sphere.h"
#include "hittable_list.h"

using namespace std;

color ray_color(const ray& r, const hittable& object)
{
	hit_record rec;
	if (object.hit(r, 0, infinity, rec))
	{
		return 0.5 * (rec.normal + vec3(1, 1, 1));
	}

	vec3 unit_r = unit_vector(r.direction());
	auto a = 0.5 + (0.5 * unit_r[1]);
	return (1 - a) * color(1.0f, 1.0f, 1.0f) + a * color(0.5f, 0.7f, 1.0f);
}

int main()
{
	// Aspect ratio calculation
	// The screen width is set by the user, and the screen height is determined based on the provided asR
	// A "virtual" viewport is created based on the aspectRatio of the screenWidth and screenHeight

	double aspectRatio = 16.0 / 9.0;

	// Dimensions of PPM
	int screen_Width = 400;
	int screen_Height = int(screen_Width / aspectRatio); // Edit 1 - asR changes due to int rounding
	screen_Height = (screen_Height < 1) ? 1 : screen_Height; // Edit 2 - asR changes to have height be at least 1

	// Camera
	point3 camera_center = point3(0, 0, 0);
	double focal_length = 1.0; // Distance from viewport and camera center | It is orthogonal - at right angles in both dimensions
	double viewport_height = 2.0; // Arbitrary number - Defines height of viewport in 3D space
	double viewport_width = viewport_height * (double(screen_Width)/screen_Height); // use the adjusted screen width and height values!

	vec3 viewport_u = vec3(viewport_width, 0, 0);
	vec3 viewport_v = vec3(0, -viewport_height, 0);
	// The world up is positive, but on the viewport, down is positive

	vec3 pixel_delta_u = viewport_u / screen_Width;
	vec3 pixel_delta_v = viewport_v / screen_Height;

	point3 viewport_ul = camera_center + vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
	point3 pixel_00_loc = viewport_ul + (0.5f * (pixel_delta_u + pixel_delta_v));

	// Define objects in world
	hittable_list existing_objects;
	existing_objects.add(make_shared<sphere>(point3(0, 0, 1), 0.5));
	existing_objects.add(make_shared<sphere>(point3(0, -100.5, 1), 100));

	// PPM format:
	// P3
	// Width Height -> space is important!
	// Max colour
	// RGB Triplets
	//...

	//Want to create an image where red increases from 0 to 256 from left to right, and green increases from 0 to 256 from top to bottom
	std::cout << "P3\n" << screen_Width << " " << screen_Height << "\n255\n";
	for (int y = 0; y < screen_Height; y++)
	{
		//std::clog << "\rScanlines left: " << (screen_Height - y) << " " << std::flush; //clog to not cause errors in ppm output
		for (int x = 0; x < screen_Width; x++)
		{
			point3 pixel_center = pixel_00_loc + x * pixel_delta_u + y * pixel_delta_v;
			vec3 ray_dir = pixel_center - camera_center;
			ray r(camera_center, ray_dir);

			write_color(std::cout, ray_color(r, existing_objects));
		}
	}
	std::clog << "\rDone!		\n";


}
