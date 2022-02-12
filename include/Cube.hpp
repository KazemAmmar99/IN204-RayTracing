#ifndef CUBE_HPP
#define CUBE_HPP

#include "Objects.hpp"

class Cube : public Object
{
private:
    float arete;
    Point3D top_front_left_corner;

public:
    Cube() : Object(CUBE), arete(1), top_front_left_corner{0, 0, 0}{};
    Cube(const Cube &anOther) : arete(anOther.arete), top_front_left_corner(anOther.top_front_left_corner), Object(anOther){};
    explicit Cube(float a) : arete(a), top_front_left_corner{0, 0, 0}, Object(CUBE){};
    Cube(float a, Point3D c) : arete(a), top_front_left_corner(c), Object(CUBE){};
    

    float getArete() { return arete; };
    Point3D getPosition() { return top_front_left_corner; };

    Point3D hit(Point3D ray_origin, Point3D ray_direction)
    {
        Point3D v = ray_origin - top_front_left_corner;

        float b = 2 * (v * ray_direction);
        float a = ray_direction * ray_direction;
        float c = v * v - arete * arete;

        float discriminent = b * b - 4 * a * c;

        if (discriminent < 0)
        {
            return Point3D(0, 0, 0);
        }
        if (discriminent == 0)
        {
            if ((b / (2 * a)) < 0)
                return ray_origin - ray_direction * (b / (2 * a));
            return Point3D(0, 0, 0);
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
            return Point3D(0, 0, 0);
        }
    };
    Point3D getNormale(Point3D intersection)
    {
        return intersection - top_front_left_corner;
    }
};

#endif