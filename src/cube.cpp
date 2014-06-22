#include "Cube.hpp"

Cube::Cube(const float x, const float y, const float size)
{   
    /* points specified from lower left corner, anti-clockwise */
    points[0] = {x, y, 1.0f};
    points[1] = {x + size, y, 1.0f};
    points[2] = {x + size, y + size, 1.0f};
    points[3] = {x, y + size, 1.0f};

} 

Cube::~Cube()
{
}




