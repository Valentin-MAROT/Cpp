#ifndef DISC_H
#define DISC_H

#include "surface.h"

class Disc : public Surface{
    private:
        Point centre;
        int rayon;
        Fill fill;
    public:
        Disc():Surface(),centre(Point(500,500)),rayon(50),fill(Color::colortype::red){};
        Disc(int rayon, Color color, Point point):Surface(),centre(point),rayon(rayon),fill(color){};
        int getRayon(){return rayon;}
        void setRayon(int rayon){this->rayon = rayon;}
        Color getColor(){return fill.getColor();}
        void setColor(Color color){fill.setColor(color);};
        int getCentreX(){return centre.getX();}
        int getCentreY(){return centre.getY();}
        void setCentreX(int x){centre.setX(x);}
        void setCentreY(int y){centre.setY(y);}
        int aire(){
            return 3.14*rayon*rayon;
        }
        virtual void translate(int x, int y){
            centre.setX(centre.getX()+x);
            centre.setY(centre.getY()+y);
        }
        virtual void scale(int x){
            rayon *= x;
        }
        virtual void rotate(int angle){
            return;
        }

        void info(){
            std::cout << "Disc" << std::endl;
            std::cout << "Rayon : " << rayon << std::endl;
            std::cout << "Aire : " << aire() << std::endl;
            std::cout << "Color : " << getColor() << "\n" << std::endl;
        }

        friend SVGstream& operator<<(SVGstream& os, Disc& disc){
            os << "<circle cx=\"" << disc.getCentreX() << "\" cy=\"" << disc.getCentreY() << "\" r=\"" << disc.rayon << "\" fill=\"" << disc.getColor() << "\" />";
            return os;
        }
};

#endif