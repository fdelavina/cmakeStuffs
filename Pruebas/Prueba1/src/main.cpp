#include <iostream>
#include "GLFW/glfw3.h"

int main()
{
    GLFWwindow *window;

    if (!glfwInit())
    {
        std::cout << "error";
        return -1;
    }
    std::cout << "hola que pasa\n";

    window = glfwCreateWindow(800,600,"hello",0,0); //create a window 
    if (!window)
    {
        std::cout << "Window creation error";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // associate opengl context to our window

    // render loop
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.8, 1.0, 1.0, 0); //fill screen with a color (r,g,b,alpha). 0.0 to 1.0
        glClear(GL_COLOR_BUFFER_BIT); // clean the screen buffer thanks to GL_COLOR_BUFFER_BIT. In OpenGL exists others buffers.
        glfwSwapBuffers(window); // presents the render frames to actual window
        glfwPollEvents(); // to process the current events
    }

    glfwTerminate();
    
}