#include "physics.hpp"
#include <iostream>

void physics_update(std::vector<Cube> &cubes, const float timestep)
{
    const vec4 gravity {0.0f, -9.81f, 0.0f, 0.0f};
    const float air_resistance = 0.95f; /* 0.2 air resistance */

    /* update positions */
    for (Cube &c : cubes) {
        /* update forces */
        c.velocity += timestep * (c.acceleration + gravity);

        /* update position */
        for (int i = 0; i < 4; ++i)
            c.points[i] = c.points[i] + timestep * c.velocity;
    }


    /* compute collisions */
    for (Cube &c : cubes) {       
        /* detect collision with objects */
/*        for (const Cube &other_c : cubes) {
            if (&c == &other_c)
                continue;

            for (int i = 0; i < 4; ++i) {
                
                c.points[i] = c.points[i]
            }
        }
*/
        /* detect collision with ground */
        float lowest_y = c.points[0].y;
        for (int i = 1; i < 4; ++i)
            lowest_y = std::min(lowest_y, c.points[i].y);


        if (lowest_y <= 0.0) {
            c.velocity.y *= -1.0;
            for (int i = 0; i < 4; ++i)
                c.points[i].y -= lowest_y;
        }
    }
}
