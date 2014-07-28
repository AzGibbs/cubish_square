#include "physics.hpp"

void physics_update(std::vector<Cube> &cubes)
{
    const dvec4 gravity {0.0, 0.05, 0.0, 0.0};
    const double air_resistance = 0.8; /* 0.2 air resistance */

    for (Cube &c : cubes) {
        c.velocity *= air_resistance;
        c.velocity -= gravity;

        /* update position */
        for (int i = 0; i < 4; ++i)
            c.points[i] = c.points[i] + c.velocity;
            

        /* detect collision with ground */
        double lowest_y = c.points[0].y;
        for (int i = 1; i < 4; ++i)
            lowest_y = std::min(lowest_y, c.points[i].y);

        if (lowest_y < 0.0) {
            c.velocity.y = 0.0;
            for (int i = 0; i < 4; ++i)
                c.points[i].y += 0.0 - lowest_y; 
        }
    }
}
