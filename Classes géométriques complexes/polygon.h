#ifndef POLYGON_H
#define POLYGON_H

#include "ReallocatablePointsArray.h"
#include <initializer_list>
using namespace std;

class Polygon : public Surface, public ReallocatablePointsArray{
    private:
            ReallocatablePointsArray points;
            Fill fill;
            int angle;
        public:
            Polygon():Surface(),points({Point(0,0), Point(100,100), Point(200,200)}),fill(Color::red),angle(0){};
            Polygon(Color::colortype color):Surface(),points({Point(0,0), Point(100,100), Point(200,200)}),fill(color),angle(0){};
            Polygon(const ReallocatablePointsArray& points,Color::colortype color):Surface(),points(points),fill(color),angle(0){};
            Polygon(const Polygon& other):Surface(other),points(other.points),angle(0){};
            Polygon(std::initializer_list<Point> list):Surface(),fill(Color::red),angle(0){
                for(auto& point : list){
                    points.setPoint(point);
                }
            }
            ~Polygon(){};
            void setPoint(const Point& point){
                points.setPoint(point);
            }
        void setPoint(const std::initializer_list<Point>& list){
            for(auto& point : list){
                points.setPoint(point);
            }
        }
        void afficherPoint(){
            points.afficherPoint();
        }
        void clear(){
            points.clear();
        }
        const int getSize()const{
            return points.getSize();
        }
        const int getCapacity()const{
            return points.getCapacity();
        }
        Point barycentre()const{
            int x = 0;
            int y = 0;
            for(int i = 0; i < points.getSize(); i++){
                x += points[i].getX();
                y += points[i].getY();
            }
            return Point(x/points.getSize(),y/points.getSize());
        }
        void setFill(const Fill& fill){
            this->fill = fill;
        }
        const Color getColor() const{
            return fill.getColor();
        }
        void setAngle(int angle){
            this->angle = angle;
        }
        const int getAngle() const{
            return angle;
        }

        void scale(int x){
            int xBarycentre = barycentre().getX();
            int yBarycentre = barycentre().getY();
            for(int i = 0; i < points.getSize(); i++){
                points[i].setX(xBarycentre+(points[i].getX()-xBarycentre)*x);
                points[i].setY(yBarycentre+(points[i].getY()-yBarycentre)*x);
            }
        }
        void translate(int dx, int dy){
            for(int i = 0; i < points.getSize(); i++){
                points[i].setX(points[i].getX()+dx);
                points[i].setY(points[i].getY()+dy);
            }
        }
        void rotate(int angle){
            setAngle(getAngle()+angle);
        }
        const ReallocatablePointsArray& getPoints() const{
            return points;
        }

        Polygon& operator=(const Polygon& other){
            if(this != &other){
                Surface::operator=(other);
                points = other.points;
            }
            return *this;
        }
        
        const Point& operator[](int index) const{
            return points[index];
        }
        Point& operator[](int index){
            return points[index];
        }

        friend SVGstream &operator<<(SVGstream &stream,const Polygon &polygon){
            stream << "<polygon points=\"";
            for(int i = 0; i < polygon.getSize(); i++){
                stream << polygon[i].getX() << "," << polygon[i].getY() << " ";
            }
            stream << "\" style=\"fill:" << polygon.getColor() << "\" transform=\"rotate(" << polygon.getAngle() << "," << polygon.barycentre().getX() << "," << polygon.barycentre().getY() << ")\" />";
            return stream;
        }
        void info(std::ostream& os)const{
            os << *this << std::endl;
        }
        void svg(SVGstream& os)const{
            os << *this;
        }
        friend std::ostream& operator<<(std::ostream& os, const Polygon& polygon){
            os << "Polygon : " << std::endl;
            os << "Fill : " << polygon.getColor() << std::endl;
            os << "Angle : " << polygon.angle << std::endl;
            os << "Taille : " << polygon.getSize() << std::endl;
            for(int i = 0; i < polygon.getSize(); i++){
                os << polygon[i] << std::endl;
            }
            return os;
        }
};

#endif