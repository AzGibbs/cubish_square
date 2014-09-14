#include "updatecubestate.hpp"

void update_master_state(std::vector<Cube> &cubes,
                         const struct Input::PrimeKeys &prime_keys)
{
    vec4 acceleration {};

    switch(prime_keys.h) {
    case Key::left:
        acceleration.x = {-10.0f};
        break;
    case Key::right:
        acceleration.x = {10.0f};
        break;
    }
    switch(prime_keys.v) {
    case Key::up:
        acceleration.y = {50.0f};
        break;
    }

    cubes[0].acceleration = acceleration;
}
