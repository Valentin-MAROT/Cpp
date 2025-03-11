#ifndef GEOM2D_H
#define GEOM2D_H
#include "transform.h"
#include "svgStream.h"
#include <iostream>
#include "point.h"

class Geom2D : public Transform{
    public:
        virtual void rotate(int angle) = 0;
        virtual void translate(int x, int y) = 0;
        virtual void scale(int x) = 0;
};
#endif