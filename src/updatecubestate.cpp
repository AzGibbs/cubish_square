#include "updatecubestate.hpp"

void update_master_state(std::vector<Cube> &cubes, const struct Input::PrimeKeys &prime_keys)
{
    dvec4 acceleration {0.0, 0.0, 0.0, 0.0};

    switch(prime_keys.h) {
    case LEFT:
        acceleration.x = {-10.0};
        break;
    case RIGHT:
        acceleration.x = {10.0};
        break;
    }
    switch(prime_keys.v) {
    case UP:
        acceleration.y = {50.0};
        break;
    }

    cubes[0].acceleration = acceleration;
}
