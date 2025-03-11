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
        int getLargeur(){return largeur;}
        int getHauteur(){return hauteur;}
        int getCentreX(){return centre.getX();}
        int getCentreY(){return centre.getY();}
        void setCentreX(int x){centre.setX(x);}
        void setCentreY(int y){centre.setY(y);}
        void setLargeur(int largeur){this->largeur = largeur;}
        void setHauteur(int hauteur){this->hauteur = hauteur;}
        Color getColor(){return fill.getColor();}
        void setColor(Color color){fill.setColor(color);}
        int aire(){
            return largeur*hauteur;
        }
        void translate(int x, int y){
            centre.setX(centre.getX()+x);
            centre.setY(centre.getY()+y);
        }
        int diagonale(){
            return sqrt(largeur*largeur+hauteur*hauteur);
        }
        int getAngle(){return angle;}
        void scale(int x){
            largeur *= x;
            hauteur *= x;
        }
        void rotate(int angle, Point& center){
            this->angle += angle;
        }
        void scale(int x){
            largeur *= x;
            hauteur *= x;
        }
        void info(){
            std::cout << "Rectangle" << std::endl;
            std::cout << "Largeur : " << largeur << std::endl;
            std::cout << "Hauteur : " << hauteur << std::endl;
            std::cout << "Aire : " << aire() << std::endl;
            std::cout << "Color : " << getColor() << std::endl;
            std::cout << "Centre : " << centre.getX() << " " << centre.getY() << std::endl;
            std::cout << "Angle : " << angle << "\n" << std::endl;
        }

        friend SVGstream& operator<<(SVGstream& os, Rectangle& rectangle){
            os << "<rect x=\"" << rectangle.getCentreX()-rectangle.largeur/2 << "\" y=\"" << rectangle.getCentreY()-rectangle.hauteur/2 << "\" width=\"" << rectangle.largeur << "\" height=\"" << rectangle.hauteur << "\" fill=\"" << rectangle.getColor() << " \" transform=\"rotate(" << rectangle.getAngle() << "," << rectangle.getCentreX() << "," << rectangle.getCentreY()<< ")\" />";
            return os;
        }
};

#endif