#ifndef SQUARE_H
#define SQUARE_H

#include "rectangle.h"

class Square : public Rectangle{
    private:
        int cote;
        Fill fill;
    public:
        Square():Rectangle(),cote(100){};
        Square(int cote, Color color,Point point):Rectangle(cote,cote,color,point),cote(cote){};
        int getCote(){return cote;}
        void setCote(int cote){this->cote = cote;}
        int aire(){
            return cote*cote;
        }
        void scale(int x){
            cote *= x;
        }
        void info(){
            std::cout << "Square" << std::endl;
            std::cout << "Cote : " << cote << std::endl;
            std::cout << "Aire : " << aire() << std::endl;
            std::cout << "Color : " << getColor() << std::endl;
            std::cout << "Centre : " << this->getCentreX() << " " << this->getCentreY() << "\n" << std::endl;
        }

        friend SVGstream& operator<<(SVGstream& os, Square& square){
            os << "<rect x=\"" << square.getCentreX()-square.cote/2 << "\" y=\"" << square.getCentreX()-square.cote/2 << "\" width=\"" << square.cote << "\" height=\"" << square.cote << "\" fill=\"" << square.getColor() << "\" style=\" transform-box: fill-box; transform-origin: center;\" transform=\"rotate(" << square.getAngle() << ")\" />";
            return os;
        }
};

#endif 