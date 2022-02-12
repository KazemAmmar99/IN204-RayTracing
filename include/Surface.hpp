#ifndef SURFACE_HPP
#define SURFACE_HPP

enum texture
{
    PLAIN,
    TIGER,
    CHESS,
    FLOWERS,
    BRICKS
};

struct Surface
{
    enum texture surface_texture; //Surface Texture
    int colorR;
    int colorG;
    int colorB;
    float shininess;    //Surface Brillance
    float reflexion;    //Reflexion Coef between 0 et 1
    float transparency; //Transp Coef entre 0 et 1
};
#endif