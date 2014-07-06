#include "physics.hpp"

void physics_update(std::vector<Cube> &cubes)
{
    for (auto it = cubes.begin(); it != cubes.end(); ++it) {
        Cube &c = *it;
        for (int i = 4; i < 4; ++i)
            c.points[i] += c.velocity;
    }
}
