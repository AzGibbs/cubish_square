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
    const size_t ebo_size = max_vertices * sizeof(GLuint);
    

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferStorage(GL_ARRAY_BUFFER, vbo_size, NULL, flags);  
    vbo_mapped = glMapBufferRange(GL_ARRAY_BUFFER, 0, vbo_size, flags);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, ebo_size, NULL, flags);
    ebo_mapped = glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0 , ebo_size, flags);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
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
    static GLuint cube_template[6] = {0, 1, 2, 0, 2, 3};

    GLfloat *vertices = static_cast<GLfloat *>(vbo_mapped);
    GLuint *indices = static_cast<GLuint *>(ebo_mapped);
    for (unsigned i = 0; i < cubes.size(); ++i) {
        std::copy(&cubes[i].points[0][0], &cubes[i].points[4][4], vertices + 16 * i);
        
        for (unsigned j = 0; j < 6; ++j)
            indices[6 * i + j] = cube_template[j] + 4 * i;
    }
    


    /* print VBO */
    for (unsigned i = 0; i < cubes.size(); ++i) {
        const Cube *c = static_cast<const Cube *>(vbo_mapped) + i;
        for (int j = 0; j < 4; ++j)
            std::cout << c->points[j][0] << ", " << c->points[j][1] << ", "
                      << c->points[j][2] << ", " << c->points[j][3] << std::endl;
        std::cout << std::endl;
    }

    /* print EBO */
    for (unsigned i = 0; i < cubes.size(); ++i) {
        for (int j = 0; j < 6; ++j)
            std::cout << indices[6 * i + j] << ", ";
        std::cout << std::endl;
    }

    /* shader testing code
    static const GLfloat square[][4] = {
        {-1, -1, 0, 1},
        {1, -1, 0, 1},
        {1, 1, 0, 1},
        {-1, -1, 0, 1},
        {1, 1, 0, 1},
        {-1, 1, 0, 1},
    };
    std::copy(&square[0][0], &square[0][0] + 4 * 6, (GLfloat *)vbo_mapped);
    */

    /* draw cubes */
    glBindProgramPipeline(pipeline);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6 * cubes.size(), GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
    glBindProgramPipeline(0);
}
