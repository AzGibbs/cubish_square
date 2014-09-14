#ifndef CUBE_HPP
#define CUBE_HPP

#include "vec.hpp"

class Cube {
public:
    Cube(const float x, const float y, const float z, const float size);
    ~Cube();

    vec4 points[4];
    vec4 velocity;
    vec4 acceleration;
};

#endif
