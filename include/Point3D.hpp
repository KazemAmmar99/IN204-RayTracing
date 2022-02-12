#ifndef POINT3D_HPP
#define POINT3D_HPP

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include <math.h>
#include <algorithm>

//We could use glm3 but we prefered to implement our own 3d point class

class Point3D
{
private:
    float pX;
    float pY;
    float pZ;

public:
    Point3D() : pX(0), pY(0), pZ(0){}; //defualt constructor
    Point3D(int x, int y, int z) : pX(x), pY(y), pZ(z){}; //explicit constructor
    Point3D(float x, float y, float z) : pX(x), pY(y), pZ(z){}; //explicit constructor
    Point3D(const Point3D &point) : pX(point.getX()), pY(point.getY()), pZ(point.getZ()){}; //copie constructor

    float getX() const
    {
        return pX;
    }
    float getY() const
    {
        return pY;
    }
    float getZ() const
    {
        return pZ;
    }

    void print()
    {
        std::cout << pX << " " << pY << " " << pZ << std::endl;
    } //To test later on te code

    void operator=(const Point3D &anotherPoint)
    {
        pX = anotherPoint.pX;
        pY = anotherPoint.pY;
        pZ = anotherPoint.pZ;
    };

    bool operator!=(const Point3D &anotherPoint) const
    {
        return (pX != anotherPoint.getX() || pY != anotherPoint.getY() || pZ != anotherPoint.getZ());
    }

    bool operator==(const Point3D &anotherPoint) const
    {
        return (pX == anotherPoint.getX() && pY == anotherPoint.getY() && pZ == anotherPoint.getZ());
    }

    Point3D operator*(float t) const
    {
        return Point3D(pX * t, pY * t, pZ * t);
    };

    friend Point3D operator*(float t, const Point3D &point);

    float operator*(const Point3D &anotherPoint) const
    {
        return (pX * anotherPoint.getX() + pY * anotherPoint.getY() + pZ * anotherPoint.getZ());
    }

    Point3D operator+(const Point3D &point) const
    {
        return Point3D(pX + point.getX(), pY + point.getY(), pZ + point.getZ());
    }

    Point3D operator-(const Point3D &point) const
    {
        return Point3D(pX - point.getX(), pY - point.getY(), pZ - point.getZ());
    }

    float dotProduct(const Point3D &anotherPoint) const
    {
        return (pX * anotherPoint.getX() + pY * anotherPoint.getY() + pZ * anotherPoint.getZ());
    }
    float norm()
    {
        return sqrt(pX * pX + pY * pY + pZ * pZ);
    }
    void normalize()
    {
        float norm = sqrt(pX * pX + pY * pY + pZ * pZ);
        pX /= norm;
        pY /= norm;
        pZ /= norm;
    }
    // Calculation of distance to the origin (to find the nearest later) (for the mmoment the origin is at (0,0,0) and we consider it known)
    Point3D min_dist(const Point3D &anotherPoint, const Point3D &origin)
    {
        float a = (*this - origin).dotProduct(*this - origin);
        float b = (anotherPoint - origin).dotProduct(anotherPoint - origin);
        if (a < b)
            return *this;
        else
            return anotherPoint;
    }
};

Point3D operator*(float t, const Point3D &point)
{
    return Point3D(point.getX() * t, point.getY() * t, point.getZ() * t);
}

#endif