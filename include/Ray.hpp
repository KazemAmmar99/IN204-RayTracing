#ifndef RAY_HPP
#define RAY_HPP

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include <math.h>
#include <algorithm>
#include "Point3D.hpp"
#include "Objects.hpp"
#include "Source.hpp"
#include <list>

#ifndef NO_HIT
#define NO_HIT  \
    {           \
        0, 0, 0 \
    }
#endif

class Rayon
{
private:
    const Point3D initial_position;
    Point3D direction; //Vector with 3 directions
public:
    Rayon() : initial_position(0, 0, 0), direction(0, 0, 1){};
    Rayon(const Point3D &aPosition, Point3D &aDirection) : initial_position(aPosition), direction(aDirection) { direction.normalize(); };

    Rayon(const Rayon &otherRay) : initial_position(otherRay.getPosition()), direction(otherRay.getDirection()){};

    Point3D getPosition() const
    {
        return initial_position;
    }
    Point3D getDirection() const
    {
        return direction;
    }
    Point3D Position_At_T(float T) const
    {
        return initial_position + direction * T;
    };

    Point3D get_Closest_Intersection(std::list<Object *> vectorOfObjects, Object *HitSphere, Point3D *norm_at_hitpoint)
    {
        
        /// Browse the vector, for each object, look for its geometry to know which equation to check,
        ///once we have the geometry, we can retrieve the position of the object and its characteristics to
        //solve the equation and store in the intersection array the point(s) of intersection of the current ray with the shapes.

        Point3D closest_intersection_point = initial_position;
        std::list<Object *>::iterator it = vectorOfObjects.begin();
        while (it != vectorOfObjects.end())
        {
            Point3D new_inter = (*it)->hit(initial_position, direction);
            if (new_inter != initial_position) // if we hit something
            {
                if ((new_inter.norm() > 0.5) && (closest_intersection_point == initial_position))
                { // If the closest has not yet been updated (it is then always equal to its initial state)
                    *HitSphere = *(*it);
                    *norm_at_hitpoint = (*it)->getNormale(new_inter);
                    closest_intersection_point = new_inter;

                } // So it's sure that he's the closest
                else if (new_inter.norm() > 0.5)
                { // If we already have a value, we compare it
                    Point3D temp = closest_intersection_point.min_dist(new_inter, initial_position);
                    if (temp != closest_intersection_point)
                    {
                        *HitSphere = *(*it);
                        *norm_at_hitpoint = (*it)->getNormale(temp);
                        closest_intersection_point = temp;
                    }
                }
            }
            std::advance(it, 1);
        }
        return closest_intersection_point;
    }
};

#endif