#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>
#include <GL/glew.h>

#include "cube.hpp"
#include "mat.hpp"


struct MVP {
    dmat4 model;
    dmat4 view;
    dmat4 projection;
};


class Renderer {
public:
    Renderer(const int width, const int height);
    ~Renderer();

    void draw(const std::vector<Cube> &cubes) const;

private:
    const int width;
    const int height;

    struct MVP mvp;

    GLuint vert_prog;
    GLuint frag_prog;
    GLuint pipeline;
    GLuint vbo;
    GLuint ebo;
    GLuint vao;
    GLuint ubo;

    void *vbo_mapped;
    void *ebo_mapped;
};

#endif
