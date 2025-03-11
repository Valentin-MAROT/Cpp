#include <iostream>
#include "disc.h"
#include "square.h"
#include "rectangle.h"
#include "svgStream.h"

int main(){
    Rectangle r(100,300,Color::colortype::red,Point(250,500));
    Rectangle r2(r);
    Point *p = new Point(250,500);

    r2.setColor(Color::colortype::green);
    r2.rotate(90, *p);

    SVGstream svg("Result.svg");
    svg  << r << r2;
    svg.close();
    return 0;
}