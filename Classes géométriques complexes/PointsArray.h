#ifndef POINTSARRAY_H
#define POINTSARRAY_H
#include "transform.h"
#include "point.h"
class PointsArray: public Transform{
    protected:
        Point* points;
        int size;
    public:
        PointsArray():Transform(),points(new Point[1]),size(1){};
        PointsArray(int size):Transform(),points(new Point[size]),size(size){};
        PointsArray(std::initializer_list<Point> &points):Transform(),points(new Point[points.size()]),size(points.size()){
            int i = 0;
            for(auto it = points.begin(); it != points.end(); it++){
                this->points[i] = *it;
                i++;
            }
        };
        PointsArray(const PointsArray& other):Transform(other),points(new Point[other.size]),size(other.size){
            for(int i = 0; i < size; i++){
                points[i] = other.points[i];
            }
        };
        ~PointsArray(){delete[] points;}
        void removePoint(int index){
            if(index >= 0 && index < size){
                Point* newPoints = new Point[size-1];
                for(int i = 0; i < index; i++){
                    newPoints[i] = points[i];
                }
                for(int i = index+1; i < size; i++){
                    newPoints[i-1] = points[i];
                }
                delete[] points;
                points = newPoints;
                size--;
            }
        }
        void afficherPoint(){
            for(int i = 0; i < size; i++){
                std::cout << points[i] << std::endl;
            }
        }
        const int getSize()const{
            return size;
        }
        Point& operator[](int index){
            return points[index];
        }
        const Point& operator[](int index) const{
            return points[index];
        }
        PointsArray& operator=(const PointsArray& other){
            if(this != &other){
                delete[] points;
                size = other.size;
                points = new Point[size];
                for(int i = 0; i < size; i++){
                    points[i] = other.points[i];
                }
            }
            return *this;
        }
        void translate(int dx, int dy){
            for(int i = 0; i < size; i++){
                points[i].setX(points[i].getX()+dx);
                points[i].setY(points[i].getY()+dy);
            }
        }
        void rotate(int angle){
            for(int i = 0; i < size; i++){
                points[i].setX(barycentre().getX() + (points[i].getX()-barycentre().getX())*cos(angle*M_PI/180) - (points[i].getY()-barycentre().getY())*sin(angle*M_PI/180));
            }
        }
        const Point barycentre()const{
            int x = 0;
            int y = 0;
            for(int i = 0; i < size; i++){
                x += points[i].getX();
                y += points[i].getY();
            }
            return Point(x/size, y/size);
        }
        void scale(int x){
            for(int i = 0; i < size; i++){
                points[i].setX(points[i].getX()*x);
                points[i].setY(points[i].getY()*x);
            }
        }

        friend std::ostream& operator<<(std::ostream& os, PointsArray& pointsArray){
            for(int i = 0; i < pointsArray.size; i++){
                os << pointsArray.points[i] << " ";
            }
            return os;
        }
    
        friend SVGstream& operator<<(SVGstream& os, PointsArray& pointsArray){
            os << "<polygon points=\"";
            for(int i = 0; i < pointsArray.size; i++){
                os << pointsArray.points[i].getX() << "," << pointsArray.points[i].getY() << " ";
            }
            os << "\" />";
            return os;
        }

};


#endif