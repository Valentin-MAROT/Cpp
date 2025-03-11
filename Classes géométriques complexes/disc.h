#ifndef DISC_H
#define DISC_H

#include "surface.h"

class Disc : public Surface
{
private:
    Point centre;
    int rayon;
    Fill fill;

public:
    Disc() : Surface(), centre(Point(500, 500)), rayon(50), fill(Color::colortype::red){};
    Disc(Color color) : Surface(), centre(Point(500, 500)), rayon(50), fill(color){};
    Disc(int rayon, Color color, Point point) : Surface(), centre(point), rayon(rayon), fill(color){};
    const int getRayon() const { return rayon; }
    void setRayon(int rayon) { this->rayon = rayon; }
    const Color getColor() const { return fill.getColor(); }
    void setColor(Color color) { fill.setColor(color); };
    const int getCentreX() const { return centre.getX(); }
    const int getCentreY() const { return centre.getY(); }
    void setCentreX(int x) { centre.setX(x); }
    void setCentreY(int y) { centre.setY(y); }
    const int aire() const
    {
        return 3.14 * rayon * rayon;
    }
    virtual void translate(int x, int y)
    {
        centre.setX(centre.getX() + x);
        centre.setY(centre.getY() + y);
    }
    virtual void scale(int x)
    {
        rayon *= x;
    }
    virtual void rotate(int angle)
    {
        return;
    }

    friend SVGstream &operator<<(SVGstream &os, const Disc &disc)
    {
        os << "<circle cx=\"" << disc.getCentreX() << "\" cy=\"" << disc.getCentreY() << "\" r=\"" << disc.rayon << "\" fill=\"" << disc.getColor() << "\" />";
        return os;
    }
    friend std::ostream &operator<<(std::ostream &os, const Disc &disc)
    {
        os << "Disc" << std::endl;
        os << "Rayon : " << disc.rayon << std::endl;
        os << "Aire : " << disc.aire() << std::endl;
        os << "Color : " << disc.getColor() << std::endl;
        return os;
    }
    void svg(SVGstream &os) const
    {
        os << *this;
    }
    void info(std::ostream &os) const
    {
        os << *this << std::endl;
    }
};

#endif