#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Objects.hpp"

class Sphere : public Object
{
private:
    float rayon;
    Point3D centre;

public:
    Sphere() : Object(SPHERE), rayon(1), centre{0, 0, 0} {};
    Sphere(const Sphere &anOther) : Object(anOther.object_surface, SPHERE), rayon(anOther.rayon), centre(anOther.centre){};
    explicit Sphere(float r) : Object(SPHERE), rayon(r), centre{0, 0, 0} {};
    Sphere(float r, const Point3D &c) : Object(SPHERE), rayon(r), centre(c){};
    Sphere(Surface surf, float r, const Point3D &c) : Object(surf, SPHERE), rayon(r), centre(c){};
    ~Sphere(){};

    void operator=(const Sphere &anotherSphere)
    {
        rayon = anotherSphere.rayon;
        centre = anotherSphere.centre;
        object_surface = anotherSphere.object_surface;
    };

    float getRay() 
    { 
        return rayon; 
    };
    Point3D getPosition() const
    {
        return centre;
    };

    Point3D getNormale(Point3D intersection)
    {
        return intersection - centre;
    }

    Point3D hit(Point3D ray_origin, Point3D ray_direction)
    {
        Point3D v = ray_origin - centre;

        float a = ray_direction * ray_direction;
        float b = 2 * (v * ray_direction);
        float c = v * v - rayon * rayon;

        float discriminent = b * b - 4 * a * c;

        if (discriminent == 0)
        {
            if ((b / (2 * a)) < 0)
                return ray_origin - ray_direction * (b / (2 * a));
            return Point3D(0, 0, 0);
        }

        if (discriminent < 0)
        {
            return NO_HIT;
        }

        else
        {
            if ((((b + sqrt(discriminent)) / (2 * a)) < 0) && (((b - sqrt(discriminent)) / (2 * a)) < 0))
                return (ray_origin - ray_direction * ((b + sqrt(discriminent)) / (2 * a))).min_dist(ray_origin - ray_direction * ((b - sqrt(discriminent)) / (2 * a)), ray_origin);
            else
            {
                if (((b + sqrt(discriminent)) / (2 * a)) < 0)
                    return (ray_origin - ray_direction * ((b + sqrt(discriminent)) / (2 * a)));
                if (((b - sqrt(discriminent)) / (2 * a)) < 0)
                    return (ray_origin - ray_direction * ((b - sqrt(discriminent)) / (2 * a)));
            }
            return NO_HIT;
        }
    };
};
#endif