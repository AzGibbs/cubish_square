#include <cstdlib>
#include <iostream>

#include <GLFW/glfw3.h>


static void error_callback(int error, const char *desc)
{
    std::cerr << desc << std::endl;
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
   
    /* general initialization code */ 

    while (!glfwWindowShouldClose(window)) {

         
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    /* free memory */
    glfwDestroyWindow(window);
    glfwTerminate();

    std::exit(EXIT_SUCCESS);
}
