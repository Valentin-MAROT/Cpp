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
        const int aire()const{
            return cote*cote;
        }
        void scale(int x){
            cote *= x;
        }
        friend std::ostream& operator<<(std::ostream& os,const Square& square){
            os << "Square" << std::endl;
            os << "Cote : " << square.cote << std::endl;
            os << "Aire : " << square.aire() << std::endl;
            os << "Color : " << square.getColor() << std::endl;
            return os;
        }
        void info(std::ostream& os) const{
            os << *this << std::endl;
        }
        void svg(SVGstream& os) const{
            os << *this;
        }

        friend SVGstream& operator<<(SVGstream& os, const Square& square){
            os << "<rect x=\"" << square.getCentreX()-square.cote/2 << "\" y=\"" << square.getCentreX()-square.cote/2 << "\" width=\"" << square.cote << "\" height=\"" << square.cote << "\" fill=\"" << square.getColor() << "\" style=\" transform-box: fill-box; transform-origin: center;\" transform=\"rotate(" << square.getAngle() << ")\" />";
            return os;
        }
};

#endif 