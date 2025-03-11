#pragma once

#include <cstdint>
    
    enum class ShapeType: uint64_t {
      Segment = 1ULL << 0,
      Triangle = 1ULL << 1,
      Carre = 1ULL << 2,
      Rectangle = 1ULL << 2,
      Polygone = 1ULL << 3,
      Pentagone = 1ULL << 3,
      Hexagone = 1ULL << 3,
      Heptagone = 1ULL << 3,
      Octogone = 1ULL << 3,
      Cercle = 1ULL << 4,
      Disk = 1ULL << 4,
      Ellipse = 1ULL << 5,
      Complexe = 1ULL << 6,
      Polyline = 1ULL << 6,
      All = 0xFFFFFFFFFFFFFFFFULL
    };

const char* ShapeTypeToString(ShapeType type);

ShapeType UllToShapeType(uint64_t type);

ShapeType operator|(ShapeType a, ShapeType b);

bool operator==(ShapeType a, ShapeType b);

bool operator&(ShapeType a, ShapeType b);

bool operator!=(ShapeType a, ShapeType b);

bool operator==(ShapeType a, uint64_t b);

bool operator!=(ShapeType a, uint64_t b);

bool operator==(uint64_t a, ShapeType b);