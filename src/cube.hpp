#ifndef CUBE_HPP
#define CUBE_HPP

class Cube {
public:
    Cube(const float x, const float y, const float z, const float size);
    ~Cube();

    float points[4][4];
};

#endif
