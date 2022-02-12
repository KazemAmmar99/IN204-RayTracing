#ifndef PLAN_HPP
#define PLAN_HPP


#include "Objects.hpp"

class Plan : public Object
{
private:
    const Point3D normal; //Vector
    const Point3D point;

public:
    Plan() : Object(PLAN), normal{1, 1, 1}, point{0, 0, 0} {};
    Plan(const Plan &otherPlan) : Object(PLAN), normal(otherPlan.normal), point(otherPlan.point){};
    Plan(const Point3D &n, const Point3D &o) : Object(PLAN), normal(n), point(o){};
    Plan(Surface surf, Point3D n, const Point3D &o) : Object(surf, PLAN), normal(n), point(o){};
    Point3D getNormale()
    {
        return normal;
    }
    Point3D getPoint() const
    {
        return point;
    }
    Point3D getNormale(Point3D intersection)
    {
        return normal;
    }

    Point3D hit(Point3D ray_origin, Point3D ray_direction)
    {
        float d = -normal.dotProduct(point); //Plane has equation ax+by+cz+d=0 where (a,b,c) is the normal vector and (x,y,z) a point in the plane

        float t = (float)-(ray_origin.dotProduct(normal) + d) / normal.dotProduct(ray_direction);
        if (t > 0)
            return ray_origin + ray_direction * t;
        return Point3D(0, 0, 0);
    };

    ~Plan(){};
};
#endif