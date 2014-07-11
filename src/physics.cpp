#include "physics.hpp"

void physics_update(std::vector<Cube> &cubes)
{
    for (Cube &c : cubes) {
        for (int i = 0; i < 4; ++i)
            c.points[i] = c.points[i] + c.velocity;
    }
}
