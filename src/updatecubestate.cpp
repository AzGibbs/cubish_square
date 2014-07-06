#include "updatecubestate.hpp"

void update_master_state(std::vector<Cube> &cubes, const KEY key)
{   
    double velocity[4] = {0.0};
    switch(key) {
    case LEFT:
        velocity[0] = -1.0;
        break;
    case RIGHT:
        velocity[0] = 1.0;
        break;
    case UP:
        velocity[1] = 1.0;
        break;
    case DOWN:
        velocity[1] = -1.0;
        break;
    }
    

    std::copy(velocity, velocity+4, cubes[0].velocity);
    
    
}

