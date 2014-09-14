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


Renderer::Renderer(const int width, const int height) : width(width), height(height), mvp{}
{
    glDebugMessageCallback(gl_debug_callback, NULL);

    const int max_vertices {100};

    const GLbitfield flags {GL_MAP_WRITE_BIT |
                            GL_MAP_PERSISTENT_BIT |
                            GL_MAP_COHERENT_BIT};
    /* factor 3 comes from euler characteristic */
    const size_t vbo_size {max_vertices * 3 * sizeof(GLfloat)};
    const size_t ebo_size {max_vertices * sizeof(GLuint)};
    const size_t vbo_lines_size {10 * 4 * sizeof(GLfloat)};

    glGenBuffers(2, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferStorage(GL_ARRAY_BUFFER, vbo_size, NULL, flags);  
    vbo_mapped = glMapBufferRange(GL_ARRAY_BUFFER, 0, vbo_size, flags);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferStorage(GL_ARRAY_BUFFER, vbo_lines_size, NULL, flags);
    vbo_lines_mapped = glMapBufferRange(GL_ARRAY_BUFFER, 0, vbo_lines_size, flags);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, ebo_size, NULL, flags);
    ebo_mapped = glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0 , ebo_size, flags);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenVertexArrays(2, vao);
    glBindVertexArray(vao[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    /* velocity VAO */
    glBindVertexArray(vao[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    /* pass through shaders */
    const std::string vert_data = read_file("data/main.vert");
    const char *vert_data_ptr = vert_data.c_str();
    vert_prog[0] = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &vert_data_ptr);

    const std::string frag_data = read_file("data/main.frag");
    const char *frag_data_ptr = frag_data.c_str();
    frag_prog[0] = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &frag_data_ptr);

    glGenProgramPipelines(2, pipeline);
    
    glUseProgramStages(pipeline[0], GL_VERTEX_SHADER_BIT, vert_prog[0]);
    glUseProgramStages(pipeline[0], GL_FRAGMENT_SHADER_BIT, frag_prog[0]);

    /* debug arrows shaders */
    const std::string frag_velocity = read_file("data/velocity.frag");
    const char *frag_velocity_ptr = frag_velocity.c_str();
    frag_prog[1] = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &frag_velocity_ptr);

    glUseProgramStages(pipeline[1], GL_VERTEX_SHADER_BIT, vert_prog[0]);
    glUseProgramStages(pipeline[1], GL_FRAGMENT_SHADER_BIT, frag_prog[1]);
    

    /* set up uniforms */
    mvp.view = {20.0f / width, 0.0f, 0.0f, 0.0f,
                0.0f, 20.0f / height, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                -1.0f, -1.0f, 0.0f, 1.0f}; 

    glGenBuffers(1, &ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferStorage(GL_UNIFORM_BUFFER, sizeof(mvp), &mvp, GL_DYNAMIC_STORAGE_BIT);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    glUniformBlockBinding(vert_prog[0], glGetUniformBlockIndex(vert_prog[0], "MVP"), 0);
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubo, 0, sizeof(mvp));
}


Renderer::~Renderer()
{
    glDeleteBuffers(2, vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(2, vao);

    glDeleteBuffers(1, &ubo);

    glDeleteProgram(vert_prog[0]);
    glDeleteProgram(frag_prog[0]);
    glDeleteProgram(frag_prog[1]);
    glDeleteProgramPipelines(2, pipeline); 
}


void Renderer::draw(const std::vector<Cube> &cubes) const
{
    static GLuint cube_template[6] {0, 1, 2, 0, 2, 3};

    /* construct cube's triangles */
    vec4 *vertices = static_cast<vec4 *>(vbo_mapped);
    GLuint *indices = static_cast<GLuint *>(ebo_mapped);
    for (unsigned i = 0; i < cubes.size(); ++i) {
        std::copy(&cubes[i].points[0], &cubes[i].points[4], vertices + 4*i);
        
        for (unsigned j = 0; j < 6; ++j)
            indices[6 * i + j] = {cube_template[j] + 4 * i};
    }

    /* construct velocity vectors */
    for (unsigned i = 0; i < cubes.size(); ++i) {
        vec4 centroid {0.0f, 0.0f, 0.0f, 0.0f};
        /* compute centroid */
        for (int j = 0; j < 4; ++j)
            centroid += 0.25f * cubes[i].points[j];

        vec4 *line = static_cast<vec4 *>(vbo_lines_mapped) + 2*i;
        line[0] = centroid;
        line[1] = centroid + cubes[i].velocity;
    }


#ifdef DEBUG_RENDERER
    /* TODO this now does not work */
    /* print VBO */
    for (unsigned i = 0; i < cubes.size(); ++i) {
        const vec4 *points = static_cast<const vec4 *>(vbo_mapped) + i;
        for (int j = 0; j < 4; ++j)
            std::cout << points[4 * i + j].x << ", " << points[4 * i + j].y << ", "
                      << points[4 * i + j].z << ", " << points[4 * i + j].w << std::endl;
        std::cout << std::endl;
    }

    /* print EBO */
    for (unsigned i = 0; i < cubes.size(); ++i) {
        for (int j = 0; j < 6; ++j)
            std::cout << indices[6 * i + j] << ", ";
        std::cout << std::endl;
    }

    for (unsigned i = 0; i < cubes.size(); ++i) {
        vec4 *lines = static_cast<vec4 *>(vbo_lines_mapped);
        std::cout << "line " << lines[2*i].x << " " << lines[2*i].y << " " << lines[2*i].z
                  << " " << lines[2*i].w
                  << ", " << lines[2*i + 1].x << " " << lines[2*i + 1].y << " "
                  << lines[2*i + 1].z << " " << lines[2*i + 1].w << std::endl;
    }
#endif

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
    glBindProgramPipeline(pipeline[0]);
    glBindVertexArray(vao[0]);
    glDrawElements(GL_TRIANGLES, 6 * cubes.size(), GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
    glBindProgramPipeline(0);

    glBindProgramPipeline(pipeline[1]);
    glBindVertexArray(vao[1]);
    glDrawArrays(GL_LINES, 0, 2 * cubes.size());
    glBindVertexArray(0);
    glBindProgramPipeline(0);
}
