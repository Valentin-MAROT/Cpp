#ifndef FILL_H
#define FILL_H
#include "color.h"

class Fill{
    private:
        Color color;
    public:
        Fill(Color color):color(color){};
        Fill():color(Color::colortype::red){};
        Fill(const Fill &f):color(f.color){};
        Fill(Color::colortype color):color(color){};
        ~Fill(){};
        Color getColor(){return color;}
        void setColor(Color color){this->color = color;}
        void afficher();
};

#endif