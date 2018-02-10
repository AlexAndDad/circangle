#include <cstdlib>
#include <bits/stdc++.h>
#include<GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>



void framebuffer_size_callback(GLFWwindow * window,int width,int height);
void processInput(GLFWwindow * window);
std::vector<float> processColor(std::vector<float> colorVector);

//settings
int SCR_WIDTH = 0;
int SCR_HEIGHT = 0;


int main() {
    //Setup glfw profile
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Detect and set video resolution
    SCR_WIDTH = glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
    SCR_HEIGHT = glfwGetVideoMode(glfwGetPrimaryMonitor())->height;


    //Create window object and check if it initialised correctly.
    GLFWwindow * window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOPenGlMofo",nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    //Initialises GLAD (using GLEW instead)
    /*if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }*/

    //Sets OPENGl viewport and registers callback function to resize it.
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    std::vector<float> colorVector = {0.0f,0.0f,0.0f,1.0f};
    //Render Loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        //rendering commands
        colorVector = processColor(colorVector);
        glClearColor(colorVector[0],colorVector[1],colorVector[2],colorVector[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        //check and call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    }




    glfwTerminate();
    return 0;
}




void framebuffer_size_callback(GLFWwindow * window,int width,int height)
{
    glViewport(0,0,width,height);
}

void processInput(GLFWwindow * window)
{
    if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);
}
std::vector<float> processColor(std::vector<float> colorVector)
{
    float r =  ((float)rand() / RAND_MAX);
    float g =  ((float)rand() / RAND_MAX);
    float b =  ((float)rand() / RAND_MAX);

    colorVector[0] = r;
    colorVector[1] = g;
    colorVector[2] = b;
    return colorVector;
}