#ifndef CUBE_HPP
#define CUBE_HPP

#include "vec.hpp"

class Cube {
public:
    Cube(const double x, const double y, const double z, const double size);
    ~Cube();

    dvec4 points[4];
    dvec4 velocity;
    dvec4 acceleration;
};

#endif
