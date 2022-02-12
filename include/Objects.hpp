#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include <math.h>
#include <algorithm>
#include "Point3D.hpp"
#include "Surface.hpp"

#ifndef NO_HIT
#define NO_HIT  \
    {           \
        0, 0, 0 \
    }
#endif

typedef struct Surface Surface;

enum geometry
{
    CUBE,
    TRIANGLE,
    RECTANGLE,
    SPHERE,
    PLAN
};

class Object
{
    //An object has surface and a geometry
protected:
    Surface object_surface;
    enum geometry object_geometry;
    int id;
    static int nbObj;

public:

    enum geometry getGeometry() 
    {
        return object_geometry; 
    };
    Surface getSurfaceProperties() 
    { 
        return object_surface; 
    };

    virtual Point3D hit(Point3D ray_origin, Point3D ray_direction)
    {
        std::cerr << "no hit available for base class" << std::endl;
        return NO_HIT;
    };

    virtual Point3D getNormale()
    {
        std::cerr << "no normal available for basic object" << std::endl;
        return NO_HIT;
    }
    virtual Point3D getNormale(Point3D pointIntersect)
    {
        std::cerr << "no normal available for basic object" << std::endl;
        return NO_HIT;
    }

    Object()
    {
        object_surface.surface_texture = PLAIN;
        object_surface.reflexion = 0;
        object_surface.transparency = 0;
        id = nbObj;
        NumberObjects();
    }
    
    explicit Object(Surface aSurface)
    {
        object_surface = aSurface;
        id = nbObj;
        NumberObjects();
    };

    Object(geometry aGeometry)
    {
        object_geometry = aGeometry;
        id = nbObj;
        NumberObjects();
    }
    Object(Surface aSurface, geometry aGeometry)
    {
        object_surface = aSurface;
        object_geometry = aGeometry;
        id = nbObj;
        NumberObjects();
    }

    Object(const Object &anOther)
    {
        object_surface = anOther.object_surface;
        id = nbObj;
        NumberObjects();
    };

    virtual ~Object(){};

    static void NumberObjects()
    {
        nbObj++;
    }
    bool operator!=(const Object &anotherObj)
    {
        return !(id == anotherObj.id);
    }
};


#endif