#ifndef CUBE_HPP
#define CUBE_HPP

class Cube {
public:
    Cube(const float x, const float y, const float z, const float size);
    ~Cube();

    double points[4][4];
    double velocity[4];
};

#endif
