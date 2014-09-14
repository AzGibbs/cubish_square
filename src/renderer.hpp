#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>
#include <GL/glew.h>

#include "cube.hpp"
#include "mat.hpp"


struct MVP {
    mat4 model;
    mat4 view;
    mat4 projection;
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

    GLuint vert_prog[2];
    GLuint frag_prog[2];
    GLuint pipeline[2];
    GLuint vbo[2];
    GLuint ebo;
    GLuint vao[2];
    GLuint ubo;

    void *vbo_mapped;
    void *ebo_mapped;
    void *vbo_lines_mapped;
};

#endif
