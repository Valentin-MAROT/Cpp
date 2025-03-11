#ifndef _COLOR_H
#define _COLOR_H
#include "SVGstream.h"
#include <cstdint>
class Color {
    public:
        enum colortype : uint8_t { red = 0, white, yellow, orange,
            turquoise, violet, pink, green, grey, cyan, blue, brown };
    private:
        static const size_t nColor = 12;
        static const char *name[];
        colortype  color;
    public:
        inline Color(const colortype &c) : color(c){}
        inline const char *getName() const { return name[color]; }
        inline void set(const colortype &c) { color = c; }
        friend inline std::ostream &operator<<(std::ostream &s, const Color &c) {
            return s << c.getName();
        }
        friend inline SVGstream& operator<<(SVGstream& s, const Color &c) {
            return s << c.getName();
        }
};

const char *Color::name[nColor] = {
    "red", "white", "yellow", "orange", "turquoise", "violet", "pink", "green",
    "grey", "cyan", "blue", "brown"
};
#endif