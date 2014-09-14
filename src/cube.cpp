#include "cube.hpp"

Cube::Cube(const float x, const float y, const float z, const float size) :
    velocity {}, acceleration {}
{   
    /* points specified from lower left corner, anti-clockwise */
    /* everything is on plane with z = 0.0f */
    points[0] = {x, y, 0.0f, 1.0f};
    points[1] = {x + size, y, 0.0f, 1.0f};
    points[2] = {x + size, y + size, 0.0f, 1.0f};
    points[3] = {x, y + size, 0.0f, 1.0f};
} 

Cube::~Cube()
{
}
