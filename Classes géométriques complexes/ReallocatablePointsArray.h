#ifndef REALLOCATABLEPOINTSARRAY_H
#define REALLOCATABLEPOINTSARRAY_H

#include "PointsArray.h"
#include <initializer_list>

class ReallocatablePointsArray : public PointsArray{
    private:
        Point* points;
        int capacity;
        int size;
    public:
        ReallocatablePointsArray():PointsArray(),capacity(1),size(0){
            points = new Point[capacity];
        };
        ReallocatablePointsArray(int capacity):PointsArray(capacity),capacity(capacity),size(0){
            points = new Point[capacity];
        };
        ReallocatablePointsArray(const ReallocatablePointsArray& other):PointsArray(other),capacity(other.capacity),size(other.size){
            points = new Point[capacity];
            for(int i = 0; i < size; i++){
                points[i] = other.points[i];
            }
        };
        ReallocatablePointsArray(std::initializer_list<Point> list):PointsArray(list.size()),capacity(list.size()),size(0){
            points = new Point[capacity];
            for(auto& point : list){
                setPoint(point);
            }
        };
        ~ReallocatablePointsArray(){delete[] points;}
        void setPoint(Point point){
            if(size == capacity){
                capacity *= 2;
                Point* newPoints = new Point[capacity];
                for(int i = 0; i < size; i++){
                    newPoints[i] = points[i];
                }
                delete[] points;
                points = newPoints;
            }
            points[size] = point;
            size++;
        }
        void setPoint(std::initializer_list<Point> list){
            for(auto& point : list){
                setPoint(point);
            }
        }

        void afficherPoint(){
            for(int i = 0; i < size; i++){
                std::cout << points[i] << std::endl;
            }
        }
        void pop_back(){
            if(size > 0){
                size--;
            }
        }
        void clear(){
            size = 0;
        }
        const int getSize()const{
            return size;
        }
        const int getCapacity()const{
            return capacity;
        }
        Point& operator[](int index){
            return points[index];
        }
        const Point& operator[](int index) const{
            return points[index];
        }
        ReallocatablePointsArray& operator=(const ReallocatablePointsArray& other){
            if(this != &other){
                delete[] points;
                capacity = other.capacity;
                size = other.size;
                points = new Point[capacity];
                for(int i = 0; i < size; i++){
                    points[i] = other.points[i];
                }
            }
            return *this;
        }
        friend std::ostream& operator<<(std::ostream& os, const ReallocatablePointsArray& pointsArray){
            os << "PointsArray : " << std::endl;
            for(int i = 0; i < pointsArray.size; i++){
                os << pointsArray.points[i] << std::endl;
            }
            return os;
        }
        void translate(int dx, int dy){
            for(int i = 0; i < size; i++){
                points[i].setX(points[i].getX() + dx);
                points[i].setY(points[i].getY() + dy);
            }
        }
        void rotate(int angle, const Point& center){
            for(int i = 0; i < size; i++){
                points[i].setX(center.getX() + (points[i].getX() - center.getX()) * cos(angle * M_PI / 180) - (points[i].getY() - center.getY()) * sin(angle * M_PI / 180));
                points[i].setY(center.getY() + (points[i].getX() - center.getX()) * sin(angle * M_PI / 180) + (points[i].getY() - center.getY()) * cos(angle * M_PI / 180));
            }
        }
        void scale(int x){
            for(int i = 0; i < size; i++){
                points[i].setX(points[i].getX() * x);
                points[i].setY(points[i].getY() * x);
            }
        }
};

#endif