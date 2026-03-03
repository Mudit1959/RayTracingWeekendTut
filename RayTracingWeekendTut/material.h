#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class material // Abstract class for materials of any kind 
{
public:

	virtual ~material() = default;

	virtual bool scatter(const ray& r_in, const hit_record& rec, 
		color& attentuation, ray&scattered) const { return false; }
};

// note the use of ray& -> this is pass by reference!
// With every call the attenuated color and the scaterred ray are edited!

// Scatter refers to when a ray of light strikes an object 
// Lambert implements the non-uniform random reflectance
// Metals implement perfect reflections
// Attentuation refers to the 

class lambertian : public material 
{
public:
    lambertian(const color& albedo) : albedo(albedo) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
        const override {
        vec3 bounce_off_dir = rec.normal + random_unit_vector();
        
        if (bounce_off_dir.near_zero()) { bounce_off_dir = rec.normal; }

        scattered = ray(rec.p, bounce_off_dir);
        attenuation = albedo;
        return true;
    }

private:
    color albedo; // refers to the color profile of the object
};

class metal : public material 
{
public:
    metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? fuzz : 1) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
        const override {
        vec3 reflected_dir = reflect(r_in.direction(), rec.normal);
        // normalize the reflected direction, then offset by a random unit vector within a sphere
        reflected_dir = unit_vector(reflected_dir) + (fuzz * random_unit_vector());
        scattered = ray(rec.p, reflected_dir);
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

private:
    color albedo;
    double fuzz;
};

class dielectric : public material 
{
public:
    dielectric(double ri) : refractive_index(ri) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
        const override {
        attenuation = color(1, 1, 1); // light is passing through

        double ri = rec.front_face ? (1.0 / refractive_index) : refractive_index; // Is the ray entering or exiting the material?

        vec3 unit_dir = unit_vector(r_in.direction()); // normalize 
        vec3 refracted = refract(unit_dir, rec.normal, ri); // calculate new direction

        // handling total internal reflection
        double cos_theta = std::fmin(dot(-unit_dir, rec.normal), 1.0);
        double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

        bool cannot_refract = ri * sin_theta > 1.0;
        vec3 direction;

        if (cannot_refract) 
        {
            direction = reflect(unit_dir, rec.normal);
        }
        else
        {
            direction = refract(unit_dir, rec.normal, ri);
        }

        scattered = ray(rec.p, direction); // starting from the point of contact, how has the light ray bent?
        return true;
    }

private:
    double refractive_index;

    static double reflectance(double cos, double refractive_index) 
    {
        auto r0 = (1 - refractive_index) * (1 + refractive_index);
        r0 = r0 * r0;
        return r0 + (1 - r0) * std::pow((1 - cos), 5);
    }
};

#endif
