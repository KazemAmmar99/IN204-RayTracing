#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Objects.hpp"

class Rectangle : public Object
{
private:
    const Point3D dimensions;
    Point3D top_front_left_corner;

public:
    Rectangle() : dimensions{1, 2, 3}, top_front_left_corner{0, 0, 0}, Object(RECTANGLE){};
    Rectangle(const Rectangle &anOther) : dimensions(anOther.dimensions), top_front_left_corner(anOther.top_front_left_corner), Object(anOther){};
    explicit Rectangle(const Point3D dim) : dimensions(dim), top_front_left_corner{0, 0, 0}, Object(RECTANGLE){};
    Rectangle(const Point3D dim, Point3D c) : dimensions(dim), top_front_left_corner(c), Object(RECTANGLE){};

    const Point3D getDim() 
    { 
        return dimensions; 
    };
    Point3D getPosition() 
    { 
        return top_front_left_corner; 
    };
};
#endif