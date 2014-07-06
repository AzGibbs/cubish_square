#ifndef CUBE_HPP
#define CUBE_HPP

class Cube {
public:
    Cube(const double x, const double y, const double z, const double size);
    ~Cube();

    double points[4][4];
};

#endif
