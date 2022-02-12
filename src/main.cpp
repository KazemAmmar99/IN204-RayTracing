#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include <cstdlib>
#include <math.h>
#include <fstream>
#include <list>
#include <string>
#include <random>

#include "../include/Ray.hpp"
#include "../include/Point3D.hpp"
#include "../include/Objects.hpp"
#include "../include/Source.hpp"
#include "../include/tinyxml2.cpp"
#include "../include/Surface.hpp"
#include "../include/Sphere.hpp"
#include "../include/Plan.hpp"
#include "../include/Cube.hpp"
#include "../include/Triangle.hpp"
#include "../include/Rectangle.hpp"

int Object::nbObj = 0;

// Background Plain
Point3D normal(0, 0, -1);
Surface surface_plan = {PLAIN, 255, 255, 255, 1000, 0.03, 0.0};
Point3D backgroundPoint(0, 0, 10000);
Plan background(surface_plan, normal, backgroundPoint);

Point3D ambient_intensity(10, 10, 10);

Point3D origin(0, 0, 0); //eye

// Light source
Source main_source;

float maxi(float a, float b) //a regular max fonction
{
    if (a < b)
        return b;
    return a;
}

float checkColorBoundaries(float color)
{
    if (color > 255)
        return 255;
    else if (color < 0)
        return 0;
    return color;
}
Point3D computeLight(Object object, Point3D norm, Point3D reflected, Point3D viewer, Source source)
{
    //Ambient Lighting and reflexion according to the Phong model
    float ir = ((object.getSurfaceProperties().colorR) * (source.getIntensity() * source.getColor().getX()) * maxi(-norm.dotProduct(source.getDirection()), 0.0) + 255 * source.getColor().getX() * pow(maxi(-reflected.dotProduct(viewer), 0.0), object.getSurfaceProperties().shininess)) / 255.99;
    ir = checkColorBoundaries(ir); //to keep the rqnge betwwen 0 qnd 255
    float ig = ((object.getSurfaceProperties().colorG) * (source.getIntensity() * source.getColor().getY()) * maxi(-norm.dotProduct(source.getDirection()), 0.0) + 255 * source.getColor().getY() * pow(maxi(-reflected.dotProduct(viewer), 0.0), object.getSurfaceProperties().shininess)) / 255.99;
    ig = checkColorBoundaries(ig);
    float ib = ((object.getSurfaceProperties().colorB) * (source.getIntensity() * source.getColor().getZ()) * maxi(-norm.dotProduct(source.getDirection()), 0.0) + 255 * source.getColor().getZ() * pow(maxi(-reflected.dotProduct(viewer), 0.0), object.getSurfaceProperties().shininess)) / 255.99;
    ib = checkColorBoundaries(ib);
    return Point3D((int)ir, (int)ig, (int)ib);
} 
//Still spheres for now but maybe we can just replace sphere and object later on
Point3D recursiveCompute(Rayon ray, std::list<Object *> vectorOfObjects, int counter)
{
    switch (counter)
    {
    case 3: //Rayon Depth of 3
        return ambient_intensity;
        break;
    default:
        Object HitSphere;
        Point3D norm_at_hitpoint;
        Point3D pointIntersect = ray.get_Closest_Intersection(vectorOfObjects, &HitSphere, &norm_at_hitpoint);

        if (pointIntersect == ray.getPosition()) //If we don't hit anything, we hit the background
            return Point3D(background.getSurfaceProperties().colorR, background.getSurfaceProperties().colorG, background.getSurfaceProperties().colorB);

        norm_at_hitpoint.normalize();
        Point3D viewer = (pointIntersect - origin);
        viewer.normalize();
        Point3D reflected_light = main_source.getDirection() - norm_at_hitpoint * 2.0 * (main_source.getDirection().dotProduct(norm_at_hitpoint)); //Reflected from light source, not from viewer
        reflected_light.normalize();
        Point3D c = computeLight(HitSphere, norm_at_hitpoint, reflected_light, viewer, main_source);

        //Shadow_ray calculation
        Point3D shadow_ray_dir;
        shadow_ray_dir = main_source.getDirection() * (-1);
        Rayon shadow_ray(pointIntersect + shadow_ray_dir * 0.01, shadow_ray_dir);
        Object sphere_hit2;
        Point3D norm_at_hitpoint2;
        Point3D shadow_ray_intersection = shadow_ray.get_Closest_Intersection(vectorOfObjects, &sphere_hit2, &norm_at_hitpoint2);
        if ((shadow_ray_intersection != shadow_ray.getPosition()) && (HitSphere != sphere_hit2))
            return Point3D(HitSphere.getSurfaceProperties().colorR / 5, HitSphere.getSurfaceProperties().colorG / 5, HitSphere.getSurfaceProperties().colorB / 5);

        //Reflected_ray calculation
        if (HitSphere.getSurfaceProperties().reflexion > 0.0)
        {
            Point3D reflected_ray_dir = ray.getDirection() - norm_at_hitpoint * 2.0 * (ray.getDirection().dotProduct(norm_at_hitpoint));
            Rayon reflected_ray = Rayon(pointIntersect + reflected_ray_dir * 0.01, reflected_ray_dir);
            Point3D res = c * (1 - HitSphere.getSurfaceProperties().reflexion) + recursiveCompute(reflected_ray, vectorOfObjects, counter + 1) * HitSphere.getSurfaceProperties().reflexion;
            return Point3D((int)checkColorBoundaries(res.getX()), (int)checkColorBoundaries(res.getY()), (int)checkColorBoundaries(res.getZ()));
        }

        return Point3D((int)checkColorBoundaries(c.getX()), (int)checkColorBoundaries(c.getY()), (int)checkColorBoundaries(c.getZ()));
        break;
    }
}

Surface randomSurface()
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 255); // define the range

    int r = distr(gen);
    int g = distr(gen);
    int b = distr(gen);
    Surface randomSurface = {PLAIN, r,g,b, 1000.0, 0.33, 0.0};
    return randomSurface;
}

int main()
{


    Point3D originPlan(0, 0, 500);

    //Scene Objects
    // Surface surface_sphere = {PLAIN, 235, 52, 119, 1000.0, 0.33, 0.0};
    // Surface surface_sphere2 = {PLAIN, 52, 232, 235, 1000.0, 0.33, 0.0};
    // Surface surface_sphere3 = {PLAIN, 235, 113, 52, 1000.0, 0.33, 0.0};

    std::list<Object *> myObjs;

    for(int i=0; i<10; ++i)
    {
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(-500, 500); // define the range
        myObjs.push_back(new Sphere(randomSurface(), 100, originPlan + Point3D(distr(gen), distr(gen), distr(gen))));
    }



    // Surface surface_sphere = randomSurface();
    // Surface surface_sphere2 = randomSurface();
    // Surface surface_sphere3 = randomSurface();


    // Sphere sphere(surface_sphere, 100, originPlan);
    // Sphere sphere2(surface_sphere2, 450, originPlan + Point3D(200, 300, 800));
    // Sphere sphere3(surface_sphere3, 200, originPlan + Point3D(230, -500, 400));

    Surface surface_plan_ground = {PLAIN, 255, 255, 255, 500, 0.33, 0};
    Point3D groundPoint(-100, 0, 0);
    Point3D normale_ground(1, 0, 0);
    Plan ground(surface_plan_ground, normale_ground, groundPoint);

    // std::list<Object *> myObjs;
    // myObjs.push_back(&sphere);
    // myObjs.push_back(&sphere2);
    // myObjs.push_back(&sphere3);
    myObjs.push_back(&ground);

    

    //Scene dimensions
    int cameraHeight = 721;
    int cameraWidth = 1281;

    // TEST PART
    int i = 1;
    for(auto element : myObjs)
    {   

        std::cout<< "Element " << i << " : Red : " << element->getSurfaceProperties().colorR << " Green : " << 
            element->getSurfaceProperties().colorG << " Blue : " << element->getSurfaceProperties().colorB << std::endl;
        ++i;
    }

    std::ofstream myImage;
    myImage.open("result/result.ppm");

    myImage << "P3\n"
            << cameraWidth << " " << cameraHeight << "\n255";

    for (int x = cameraHeight / 2; x >= -cameraHeight / 2; x--)
    {
        myImage << "\n";
        for (int y = -cameraWidth / 2; y <= cameraWidth / 2; y++)
        {
            Point3D aDirection(x, y, (int)originPlan.getZ());
            Rayon ray(origin, aDirection);
            Point3D my_pixel(0, 0, 0);
            my_pixel = recursiveCompute(ray, myObjs, 0);
            myImage
                << my_pixel.getX() << " " << my_pixel.getY() << " " << my_pixel.getZ() << " ";
        }
    }
    myImage.close();
    return 0;
}
