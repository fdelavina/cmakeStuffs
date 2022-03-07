#include <iostream>
#include "GLFW/glfw3.h"
#include <sstream>

float lastTime;
int nbFrames;
void showFPS(GLFWwindow *pWindow)
{
    // Measure speed
     double currentTime = glfwGetTime();
     double delta = currentTime - lastTime;
     nbFrames++;
     if ( delta >= 1.0 ){ // If last cout was more than 1 sec ago
         //std::cout << 1000.0/double(nbFrames) << std::endl;

         double fps = double(nbFrames) / delta;

         std::stringstream ss;

         ss << " [" << fps << " FPS]";

         glfwSetWindowTitle(pWindow, ss.str().c_str());

         nbFrames = 0;
         lastTime = currentTime;
     }
}

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

        //draw triangle
        glBegin(GL_TRIANGLES);

        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(-0.5f,-0.4f,0.0f);

        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(-0.5f,0.4f,0.0f);

        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(0.5f,-0.4f,0.0f);

        glEnd();

        glfwSwapBuffers(window); // presents the render frames to actual window
        glfwPollEvents(); // to process the current events


        showFPS (window);

        
    }

    glfwTerminate();
    
}