#include <iostream>
#include "GLFW/glfw3.h"
#include <sstream>
#include <math.h>

const float radius = 1.0;
const int steps = 150000;
const float angle = 3.1415926 * 2.f /steps;

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

    float xPos = 0; 
    float yPos = 0; 
    float zPos = 0; 
    // render loop
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.8, 1.0, 1.0, 0); //fill screen with a color (r,g,b,alpha). 0.0 to 1.0
        glClear(GL_COLOR_BUFFER_BIT); // clean the screen buffer thanks to GL_COLOR_BUFFER_BIT. In OpenGL exists others buffers.

        float prevX = xPos;
        float prevY = yPos - radius;
        //draw circle

        for (int i=0; i<=steps;i++)
        {
            float newX = radius * sin(angle*i);
            float newY = -radius * cos(angle*i);
            glBegin(GL_TRIANGLES);
            glColor3f(0.0,0.0,1.0);
            glVertex3f(0.0f,0.0f,0.0f);
            glVertex3f(prevX,prevY,0.0f);
            glVertex3f(newX,newY,0.0f);
            glEnd();
            prevX = newX;
            prevY = newY;

        }

        glEnd();

        glfwSwapBuffers(window); // presents the render frames to actual window
        glfwPollEvents(); // to process the current events


        showFPS (window);

        
    }

    glfwTerminate();
    
}