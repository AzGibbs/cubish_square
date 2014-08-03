#include "physics.hpp"
#include <iostream>

void physics_update(std::vector<Cube> &cubes)
{
    const dvec4 gravity {0.0, 0.05, 0.0, 0.0};
    const double air_resistance = 0.8; /* 0.2 air resistance */

    for (Cube &c : cubes) {
//        c.velocity *= air_resistance;
        std::cout << "velocity " << c.velocity.y << std::endl;
        c.velocity -= gravity;

        /* update position */
        for (int i = 0; i < 4; ++i)
            c.points[i] = c.points[i] + c.velocity;
            

        /* detect collision with ground */
        double lowest_y = c.points[0].y;
        for (int i = 1; i < 4; ++i)
            lowest_y = std::min(lowest_y, c.points[i].y);

        if (lowest_y <= 0.0) {
            std::cout << lowest_y << std::endl;
//            c.velocity.y += lowest_y;
            c.velocity.y *= -1.0;
            c.velocity += gravity;
 /*           for (int i = 0; i < 4; ++i)
                c.points[i].y -= lowest_y;*/
        }
        std::cout << std::endl;
    }
}
