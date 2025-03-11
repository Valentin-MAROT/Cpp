#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "PointsArray.h"
#include <initializer_list>

class Triangle: public Surface, public PointsArray{
    private:
        Fill fill;
        int angle;
    public:
        Triangle():Surface(),PointsArray(3),fill(Color::colortype::red),angle(0){};
        Triangle(const Triangle& other):Surface(other),PointsArray(other),fill(other.fill),angle(other.angle){};
        Triangle(Point p1, Point p2, Point p3, Color color):Surface(),PointsArray(3),fill(color),angle(0){
            points[0] = p1;
            points[1] = p2;
            points[2] = p3;
        };
        Triangle(PointsArray &points, Color color):Surface(),PointsArray(points),fill(color),angle(0){
        };
        Triangle(std::initializer_list<Point> list):Surface(),PointsArray(list),fill(Color::colortype::red),angle(0){
            if(list.size() != 3){
                throw std::invalid_argument("Triangle must have 3 points");
            }
        };
        ~Triangle(){};
        void rotate(int angle){
            this->angle += angle;
        }
        void translate(int x, int y){
            for(int i = 0; i < size; i++){
                points[i].setX(points[i].getX()+x);
                points[i].setY(points[i].getY()+y);
            }
        }
        void scale(int x){
            int xBarycentre = barycentre().getX();
            int yBarycentre = barycentre().getY();
            for(int i = 0; i < size; i++){
                points[i].setX(xBarycentre+(points[i].getX()-xBarycentre)*x);
                points[i].setY(yBarycentre+(points[i].getY()-yBarycentre)*x);
            }
        }
        void setFill(const Fill& fill){
            this->fill = fill;
        }
        const Fill& getFill() const{
            return fill;
        }
        Point barycentre()const{
            int x = 0;
            int y = 0;
            for(int i = 0; i < size; i++){
                x += points[i].getX();
                y += points[i].getY();
            }
            return Point(x/size,y/size);
        }
        const int getAngle()const{
            return angle;
        }
        Triangle& operator=(const Triangle& other){
            if(this != &other){
                Surface::operator=(other);
                points = other.points;
                fill = other.fill;
            }
            return *this;
        }
        friend SVGstream& operator<<(SVGstream& os,const Triangle &t) {
            return os << "<polygon points=\"" << t.points[0].getX() << "," << t.points[0].getY() << " " << t.points[1].getX() << "," << t.points[1].getY()<< " " << t.points[2].getX() << "," << t.points[2].getY()<<"\" fill=\"" << t.getColor() << "\" transform=\"rotate( " << t.getAngle() << "," << t.barycentre().getX() << "," << t.barycentre().getY() << ")\" />";
        }
        void info(std::ostream& os)const{
            os << *this << std::endl;
        }

        void svg(SVGstream& os)const{
            os << *this;
        }
        friend std::ostream& operator<<(std::ostream& os, const Triangle& t){
            os << "Triangle : " << std::endl;
            for(int i = 0; i < t.size; i++){
                os << t.points[i] << std::endl;
            }
            return os;
        }
};

#endif