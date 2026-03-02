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
    metal(const color& albedo) : albedo(albedo) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
        const override {
        vec3 reflected_dir = reflect(r_in.direction(), rec.normal);
        scattered = ray(rec.p, reflected_dir);
        attenuation = albedo;
        return true;
    }

private:
    color albedo;
};

#endif
