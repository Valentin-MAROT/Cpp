#ifndef GEOM2D_H
#define GEOM2D_H
#include "transform.h"
#include "point.h"

class Geom2D : public Transform{
    public:
        virtual void rotate(int angle) = 0;
        virtual void translate(int x, int y) = 0;
        virtual void scale(int x) = 0;
        virtual void info(std::ostream& os) const = 0;
        virtual void svg(SVGstream& os) const = 0;

        friend std::ostream& operator<<(std::ostream& os, const Geom2D& geom2D){
            geom2D.info(os);
            return os;
        }
        friend SVGstream& operator<<(SVGstream& os, const Geom2D& geom2D){
            geom2D.svg(os);
            return os;
        }
        virtual ~Geom2D(){}
};
#endif