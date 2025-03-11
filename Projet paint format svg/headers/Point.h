#ifndef POINT_H
#define POINT_H
#define _USE_MATH_DEFINES
#include <cmath>
#include "SVG.h"
class Point{
    private:
        int x;
        int y;
    public:
        Point(int x, int y):x(x),y(y){};
        Point():x(0),y(0){};
        Point(const Point &p):x(p.x),y(p.y){};
        Point(int x):x(x),y(0){};
        ~Point(){};
        int getX()const{return x;
        }
        int getY()const{return y;}
        void setX(int x){this->x = x;}
        void setY(int y){this->y = y;}
        friend std::ostream& operator<<(std::ostream& s, const Point& p){
            return s << "(" << p.x << "," << p.y << ")";
        }
        Point operator+(const Point& p){
            return Point(x+p.x,y+p.y);
        }

};

#endif