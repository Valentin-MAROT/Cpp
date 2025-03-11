#ifndef SURFACE_H
#define SURFACE_H

#include "fill.h"
#include "Geom2D.h"
#include <math.h>
class Surface : public Fill, public Geom2D{
    public:
        int aire();
        void info();
        virtual void rotate(int angle)=0;
        virtual void translate(int x, int y) = 0;
        virtual void scale(int x) = 0;
        virtual void info(std::ostream& os) const = 0;
        virtual void svg(SVGstream& os) const = 0;
};

#endif