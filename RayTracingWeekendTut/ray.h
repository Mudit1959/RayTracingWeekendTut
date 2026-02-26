#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
public:
    ray() {}

    ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

    const point3& origin() const { return orig; }
    const vec3& direction() const { return dir; }

    point3 at(double t) const {
        return orig + (t*dir);
    }

private:
    point3 orig;
    vec3 dir;
};

/*Hard - coded sphere
double hit_sphere(const point3& center, double radius, const ray& r) 
{
    vec3 oc = center - r.origin();
    
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - (radius * radius);

    auto discriminant = (h*h) - (a * c);

    if (discriminant < 0) 
    {
        return -1;
    }
    else { return (h - std::sqrt(discriminant)) / (a); }
}*/

#endif