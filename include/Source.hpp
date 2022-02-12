#ifndef SOURCE_HPP
#define SOURCE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include <math.h>
#include <algorithm>
#include "Point3D.hpp"

class Source
{ //the source is unidirectionnal
private:
    Point3D direction;
    Point3D color;
    float intensity; //between ntre 0 et 1
public:
    Source() : direction{-500, -500, 0}, color{255, 255, 255}, intensity(1) { direction.normalize(); }; // random default direction

    // explicit constructor
    explicit Source(const Point3D &aDirection) : direction(aDirection), color{255, 255, 255}, intensity(1){};

    // copie constructor

    Source(const Source &otherSource)
    {
        direction = otherSource.direction;
        color = otherSource.color;
        intensity = otherSource.intensity;
    }

    // Destructor

    ~Source(){}

    Point3D getColor() const
    {
        return color;
    };
    Point3D getDirection() const
    {
        return direction;
    };
    float getIntensity() const
    {
        return intensity;
    };
};

#endif