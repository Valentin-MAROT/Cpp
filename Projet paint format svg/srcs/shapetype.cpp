#include "../headers/shapetype.h"

const char* ShapeTypeToString(ShapeType type){
    switch (type)
    {
    case ShapeType::Segment:
        return "Segment";
        break;
    case ShapeType::Polygone:
        return "Polygone";
        break;
    case ShapeType::Rectangle:
        return "Rectangle";
        break;
    case ShapeType::Triangle:
        return "Triangle";
        break;
    case ShapeType::Cercle:
        return "Cercle";
        break;
    case ShapeType::Ellipse:
        return "Ellipse";
        break;
    default:
        return "Complexe";
        break;
    }
}

ShapeType UllToShapeType(uint64_t type){
    switch (type)
    {
    case 1:
        return ShapeType::Segment;
        break;
    case 2:
        return ShapeType::Polygone;
        break;
    case 8:
        return ShapeType::Rectangle;
        break;
    case 4:
        return ShapeType::Triangle;
        break;
    case 16:
        return ShapeType::Cercle;
        break;
    case 32:
        return ShapeType::Ellipse;
        break;
    default:
        return ShapeType::Complexe;
        break;
    }
}

ShapeType operator|(ShapeType a, ShapeType b){
    return static_cast<ShapeType>(static_cast<uint64_t>(a) | static_cast<uint64_t>(b));
}

bool operator==(ShapeType a, ShapeType b){
    return static_cast<uint64_t>(a) == static_cast<uint64_t>(b);
}

bool operator&(ShapeType a, ShapeType b){
    return static_cast<uint64_t>(a) & static_cast<uint64_t>(b);
}

bool operator!=(ShapeType a, ShapeType b){
    return static_cast<uint64_t>(a) != static_cast<uint64_t>(b);
}

ShapeType operator>>=(ShapeType a, ShapeType b){
    uint64_t c = static_cast<uint64_t>(a);
    uint64_t d = static_cast<uint64_t>(b);
    return static_cast<ShapeType>(c >>= d);
}

bool operator==(ShapeType a, uint64_t b){
    return static_cast<uint64_t>(a) == b;
}

bool operator!=(ShapeType a, uint64_t b){
    return static_cast<uint64_t>(a) != b;
}

bool operator==(uint64_t a, ShapeType b){
    return a == static_cast<uint64_t>(b);
}

unsigned long long int operator|(ShapeType a, unsigned long long int b){
    return static_cast<uint64_t>(a) | b;
}

