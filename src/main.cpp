#include <cstdlib>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "cube.hpp"
#include "input.hpp"
#include "renderer.hpp"


static void error_callback(int error, const char *desc)
{
    std::cerr << desc << std::endl;
}


void get_key_callback(GLFWwindow *window, int key, int scancode,
                      int action, int mods)
{
    /* TODO static, dynamic cast? */
    Input *input = (Input *)glfwGetWindowUserPointer(window);
    input->get_key_callback(key, scancode, action, mods);
}


int main(void)
{
    const int width = 800;
    const int height = 600;

    /* initialize GLFW window and OpenGL context */
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        std::exit(EXIT_FAILURE); 
    }

    /* OpenGL 4.4 with debug */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(width, height, "Cubish Square", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cerr << "Failed to create window" << std::endl;
        std::exit(EXIT_FAILURE);
    }
        
    glfwMakeContextCurrent(window);

    /* initialize GLEW to load OpenGL extensions */
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        glfwDestroyWindow(window);
        glfwTerminate();
        std::cerr << "Failed to initialize GLEW" << std::endl;
        std::exit(EXIT_FAILURE);
    }
   
    /* general initialization code */ 
    const Cube cube1 = Cube(0.0f, 0.0f, 0.0f, 10.0f);
    const Cube cube2 = Cube(0.0f, 10.0f, 0.0f, 20.0f);
    const Cube cube3 = Cube(20.0f, 0.0f, 0.0f, 10.0f);
    const Cube cube4 = Cube(30.0f, 30.0f, 0.0f, 50.0f);
    const std::vector<Cube> cubes = {cube1, cube2, cube3, cube4};

    Renderer renderer(width, height); 
    
    Input input = Input();
    glfwSetWindowUserPointer(window, (void *)&input);
    glfwSetKeyCallback(window, get_key_callback); 

    while (!glfwWindowShouldClose(window)) {
        renderer.draw(cubes);        

        std::cout << input.return_key() << std::endl; 

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    /* free memory */
    glfwDestroyWindow(window);
    glfwTerminate();

    std::exit(EXIT_SUCCESS);
}
