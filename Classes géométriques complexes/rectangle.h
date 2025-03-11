#ifndef rectangle_h
#define rectangle_h

#include "surface.h"

class Rectangle : public Surface{
    private:
        int largeur;
        int hauteur;
        Point centre;
        Fill fill;
        int angle;
    public:
        
        Rectangle():Surface(),largeur(100),hauteur(50),centre(Point(500,500)),fill(Color::colortype::red),angle(0){};
        Rectangle(int largeur, int hauteur, Color color, Point point):Surface(),largeur(largeur),hauteur(hauteur),centre(point),fill(color),angle(0){};
        Rectangle(Rectangle &rectangle):Surface(),largeur(rectangle.largeur),hauteur(rectangle.hauteur),centre(Point(rectangle.getCentreX(),rectangle.getCentreY())),fill(rectangle.getColor()),angle(rectangle.angle){};
        Rectangle(int largeur, int hauteur, Color color, Point point, int angle):Surface(),largeur(largeur),hauteur(hauteur),centre(point),fill(color),angle(angle){};
        Rectangle(Rectangle &rectangle, int angle):Surface(),largeur(rectangle.largeur),hauteur(rectangle.hauteur),centre(Point(rectangle.getCentreX(),rectangle.getCentreY())),fill(rectangle.getColor()),angle(angle){};
        const int getLargeur()const{return largeur;}
        const int getHauteur()const{return hauteur;}
        const int getCentreX()const{return centre.getX();}
        const int getCentreY()const{return centre.getY();}
        void setCentreX(int x){centre.setX(x);}
        void setCentreY(int y){centre.setY(y);}
        void setLargeur(int largeur){this->largeur = largeur;}
        void setHauteur(int hauteur){this->hauteur = hauteur;}
        const Color getColor()const{return fill.getColor();}
        void setColor(Color color){fill.setColor(color);}
        const int aire()const{
            return largeur*hauteur;
        }
        void translate(int x, int y){
            centre.setX(centre.getX()+x);
            centre.setY(centre.getY()+y);
        }
        const int diagonale()const{
            return sqrt(largeur*largeur+hauteur*hauteur);
        }
        const int getAngle()const{return angle;}
        void scale(int x){
            largeur *= x;
            hauteur *= x;
        }
        void rotate(int angle){
            this->angle += angle;
        }
        friend std::ostream& operator<<(std::ostream& os,const Rectangle& rectangle){
            os << "Rectangle" << std::endl;
            os << "Largeur : " << rectangle.largeur << std::endl;
            os << "Hauteur : " << rectangle.hauteur << std::endl;
            os << "Aire : " << rectangle.aire() << std::endl;
            os << "Color : " << rectangle.getColor() << "\n" << std::endl;
            return os;
        }
        void info(std::ostream& os)const{
            os << *this << std::endl;
        }
        void svg(SVGstream& os) const{
            os << *this;
        }

        friend SVGstream& operator<<(SVGstream& os, const Rectangle& rectangle){
            os << "<rect x=\"" << rectangle.getCentreX()-rectangle.largeur/2 << "\" y=\"" << rectangle.getCentreY()-rectangle.hauteur/2 << "\" width=\"" << rectangle.largeur << "\" height=\"" << rectangle.hauteur << "\" fill=\"" << rectangle.getColor() << " \" transform=\"rotate(" << rectangle.getAngle() << "," << rectangle.getCentreX() << "," << rectangle.getCentreY()<< ")\" />";
            return os;
        }
};

#endif