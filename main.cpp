#include <cstdlib>

#include<GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <tgmath.h>

#include "Setup/OpenGLSetup.h"
#include "Shaders/Shaders.h"
#include <boost/filesystem.hpp>
#include "stb/stb_image.h"


//void framebuffer_size_callback(GLFWwindow * window,int width,int height);
void processInput(GLFWwindow * window);
std::vector<float> processColor(std::vector<float> colorVector);





int main(int argc, const char* argv[]) {

    Shaders::deduceRoot(argv[0]);



    OpenGLSetup default_setup;
    default_setup.setup();


// build and compile our shader program

    Shaders ourShader("VertexShader.glsl","FragmentShader.glsl");


    //-----------------------------------------------------------------------


    float vertices[] = {
            //Positions            //colors
              0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // top right
             -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // bottom right
              0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f   // bottom left
    };



    //Generate buffers for vertices0
    unsigned int VAO,VBO;
    glGenBuffers(1,&VBO);
    glGenVertexArrays(1,&VAO);

    //Bind vertex array object
    glBindVertexArray(VAO);

    //Bind Vertex buffer object, declare data.
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    //Set vertex attribute pointers for vertices
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    //Set vertex attribute pointer for colors
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);



    //-----------------------------------------------------------------------------------


    //Background color vector init;
    std::vector<float> colorVector = {0.0f,0.0f,0.0f,1.0f};


    //Render Loop
    while (!glfwWindowShouldClose(default_setup.window))
    {
        // input
        processInput(default_setup.window);

        //rendering commands

        colorVector = processColor(colorVector);
        glClearColor(colorVector[0],colorVector[1],colorVector[2],colorVector[3]);
        //glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        ourShader.use();
        //ourShader.setFloat("horOffset",0);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);

       /* float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue)/2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram,"ourColor");
        glUniform4f(vertexColorLocation,0.0f,greenValue,0.0f,1.0f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);
        */




        //check and call events and swap buffers
        glfwSwapBuffers(default_setup.window);
        glfwPollEvents();
    }




    glfwTerminate();
    return 0;
}




//void framebuffer_size_callback(GLFWwindow * window,int width,int height)
//{
//    glViewport(0,0,width,height);
//}

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











