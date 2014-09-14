#ifndef UPDATECUBESTATE_HPP
#define UPDATECUBESTATE_HPP

#include <vector>

#include "cube.hpp"
#include "input.hpp"


void update_master_state(std::vector<Cube> &cubes,
                         const struct Input::PrimeKeys &prime_keys);

#endif
