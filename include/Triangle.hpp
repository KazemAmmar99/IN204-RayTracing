#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP


#include "Objects.hpp"

class Triangle : public Object 
{
private:
    float arete;
    Point3D top;

public:
    Triangle() : arete(1), top{0, 0, 0}, Object(TRIANGLE){};
    Triangle(const Triangle &anOther) : arete(anOther.arete), top(anOther.top), Object(anOther){};
    explicit Triangle(float a) : arete(a), top{0, 0, 0}, Object(TRIANGLE){};
    Triangle(float a, Point3D c) : arete(a), top(c), Object(TRIANGLE){};

    float getArete() { return arete; };
    Point3D getPosition() { return top; };
};

#endif