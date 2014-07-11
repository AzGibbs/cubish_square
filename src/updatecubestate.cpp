#include "updatecubestate.hpp"

void update_master_state(std::vector<Cube> &cubes, const KEY key)
{   
    dvec4 velocity {};

    switch(key) {
    case LEFT:
        velocity.x = {-1.0};
        break;
    case RIGHT:
        velocity.x = {1.0};
        break;
    case UP:
        velocity.y = {1.0};
        break;
    case DOWN:
        velocity.y = {-1.0};
        break;
    case NONE:
        break;
    }   

    cubes[0].velocity = {velocity};
}
