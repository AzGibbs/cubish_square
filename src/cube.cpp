#include "cube.hpp"

Cube::Cube(const double x, const double y, const double z, const double size)
{   
    /* points specified from lower left corner, anti-clockwise */
    /* everything is on plane with z = 0.0f */
    points[0] = dvec4(x, y, 0.0, 1.0);
    points[1] = dvec4(x + size, y, 0.0, 1.0);
    points[2] = dvec4(x + size, y + size, 0.0, 1.0);
    points[3] = dvec4(x, y + size, 0.0, 1.0);

    velocity = dvec4(0.0, 0.0, 0.0, 0.0);
} 

Cube::~Cube()
{
}
