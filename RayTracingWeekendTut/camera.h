#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"
#include "hittable.h"
#include "material.h"

class camera 
{
public:
	double aspectRatio = 0;
	int screen_Width = 0;
	int samples_per_pixel = 0;
	int max_depth = 0;

	double vfov = 90;
	point3 world_pos = point3(0, 0, 0);
	point3 look_at = point3(0, 0, -1);
	vec3 v_up = vec3(0, 1, 0);

	double defocus_angle = 0;
	double focus_dist = 10;

	void render(const hittable& objects) 
	{
		initialize(); // Private constructor -> Only one instance exists at any given point of time

		// PPM format:
		// P3
		// Width Height -> space is important!
		// Max colour
		// RGB Triplets
		//...

		std::cout << "P3\n" << screen_Width << " " << screen_Height << "\n255\n";
		for (int y = 0; y < screen_Height; y++)
		{
			//std::clog << "\rScanlines left: " << (screen_Height - y) << " " << std::flush; //clog to not cause errors in ppm output
			for (int x = 0; x < screen_Width; x++)
			{
				color final_color(0,0,0);

				for (int sample = 0; sample < samples_per_pixel; sample++) 
				{
					ray r = get_ray(x, y);
					final_color += ray_color(r, max_depth, objects);
				}
				write_color(std::cout, final_color * averageDenominator);
			}
		}
		std::clog << "\rDone!		\n";
	}

private:

	
	int screen_Height; // Height of the screen
	point3 camera_center; // Same as its world pos

	double averageDenominator; // Averaging out a pixel's final color
	
	double focal_length; // Defined by field of view -> Distance of camera from projection plane
	double viewport_height; 
	double viewport_width;
	vec3 viewport_u;
	vec3 viewport_v;

	vec3 pixel_delta_u; // to move by one pixel HORIZONTALLY along the viewport
	vec3 pixel_delta_v; // to move by one pixel VERTICALLY along the viewport
	point3 viewport_ul; // The upper left corner of the viewport
	point3 pixel_00_loc; // Offseted from upper left corner by half a pixel along both axes

	vec3 u, v, w;

	vec3 defocus_disk_u;
	vec3 defocus_disk_v;

	void initialize() 
	{
		// Aspect ratio calculation
	// The screen width is set by the user, and the screen height is determined based on the provided asR
	// A "virtual" viewport is created based on the aspectRatio of the screenWidth and screenHeight
		
		averageDenominator = 1.0 / samples_per_pixel;

		// Dimensions of PPM
		// Define screen width and aspect ratio in main!
		// 
		screen_Height = int(screen_Width / aspectRatio); // Edit 1 - asR changes due to int rounding
		screen_Height = (screen_Height < 1) ? 1 : screen_Height; // Edit 2 - asR changes to have height be at least 1

		// Camera
		camera_center = world_pos;
		// Without blur - focal_length = (look_at - world_pos).length(); // Distance from viewport and camera center | It is orthogonal - at right angles in both dimensions
		auto h = std::tan(degrees_to_radians(vfov) / 2);
		viewport_height = 2.0 * h * focus_dist; // Arbitrary number - Defines height of viewport in 3D space
		viewport_width = viewport_height * (double(screen_Width) / screen_Height); // use the adjusted screen width and height values!

		w = unit_vector(look_at - world_pos); // Camera forward
		u = unit_vector(cross(v_up, w)); // Camera right
		v = cross(w, u); // Camera up

		viewport_u = viewport_width * u;
		viewport_v = viewport_height * -v;
		// The world up is positive, but on the viewport, down is positive

		pixel_delta_u = viewport_u / screen_Width;
		pixel_delta_v = viewport_v / screen_Height;

		viewport_ul = camera_center + (focus_dist*w) - viewport_u / 2 - viewport_v / 2;
		pixel_00_loc = viewport_ul + (0.5f * (pixel_delta_u + pixel_delta_v));

		// ???
		auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
		defocus_disk_u = u * defocus_radius;
		defocus_disk_v = v * defocus_radius;

	}

	ray get_ray(int x, int y) const
	{
		auto offset = sample_square();
		point3 pixel_sampling = pixel_00_loc +
			((x + offset.x()) * pixel_delta_u) +
			((y + offset.y()) * pixel_delta_v);

		vec3 ray_dir = (pixel_sampling - camera_center);
		auto ray_origin = (defocus_angle <= 0) ? camera_center : defocus_sample();

		return ray(camera_center, ray_dir);
	}

	vec3 sample_square() const
	{
		return vec3(random_double() - 0.5, random_double() - 0.5, 0);
	}

	point3 defocus_sample() const
	{
		auto p = random_in_unit_disk();
		return camera_center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
	}

	color ray_color(const ray&r, int depth, const hittable& objects) const
	{
		if (depth == 0) { return color(0, 0, 0); }

		hit_record rec;

		if (objects.hit(r, interval(0.001, infinity), rec))
		{
			// Variables to be initialized by reference
			ray scatter;
			color attenuation;

			if (rec.mat->scatter(r, rec, attenuation, scatter)) 
			{
				return attenuation * ray_color(scatter, depth - 1, objects);
			}
			return color(0, 0, 0);
		}

		vec3 unit_r = unit_vector(r.direction());
		auto a = 0.5 + (0.5 * unit_r[1]);
		return (1 - a) * color(1.0f, 1.0f, 1.0f) + a * color(0.5f, 0.7f, 1.0f);
	}
};

#endif