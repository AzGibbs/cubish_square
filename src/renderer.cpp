#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "renderer.hpp"


std::string read_file(const std::string &filename)
{
    /* TODO handle error if file is non-existant */
    std::ifstream fin(filename);
    std::ostringstream out;
    out << fin.rdbuf();
    fin.close();
    
    return out.str();
}


void gl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
                       GLsizei len, const GLchar *message, void *user_param)
{
    std::cerr << message << std::endl;
}


Renderer::Renderer(const int width, const int height) : width(width), height(height)
{
    glDebugMessageCallback(gl_debug_callback, NULL);

    const int max_vertices = 100;

    const GLbitfield flags = GL_MAP_WRITE_BIT |
                             GL_MAP_PERSISTENT_BIT |
                             GL_MAP_COHERENT_BIT;
    const size_t vbo_size = max_vertices * 3 * sizeof(GLfloat);
    

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferStorage(GL_ARRAY_BUFFER, vbo_size, NULL, flags);  
    vbo_mapped = glMapBufferRange(GL_ARRAY_BUFFER, 0, vbo_size, flags);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    /* pass through shaders */
    const std::string vert_data = read_file("data/main.vert");
    const char *vert_data_ptr = vert_data.c_str();
    vert_prog = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &vert_data_ptr);

    const std::string frag_data = read_file("data/main.frag");
    const char *frag_data_ptr = frag_data.c_str();
    frag_prog = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &frag_data_ptr);

    glGenProgramPipelines(1, &pipeline);
    
    glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, vert_prog);
    glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, frag_prog);
}


Renderer::~Renderer()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    glDeleteProgram(vert_prog);
    glDeleteProgram(frag_prog);
    glDeleteProgramPipelines(1, &pipeline); 
}


void Renderer::draw(const std::vector<Cube> &cubes) const
{
    /* copy cubes to video card */
    std::copy(cubes.cbegin(), cubes.end(), (Cube *)vbo_mapped);

    static const GLfloat square[][4] = {
        {-1, -1, 0, 1},
        {1, -1, 0, 1},
        {1, 1, 0, 1},
        {-1, -1, 0, 1},
        {1, 1, 0, 1},
        {-1, 1, 0, 1},
    };

    std::copy(&square[0][0], &square[0][0] + 4 * 6, (GLfloat *)vbo_mapped);

    /* draw cubes */
    glBindProgramPipeline(pipeline);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    glBindProgramPipeline(0);
}
