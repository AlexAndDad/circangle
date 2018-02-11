#include <cstdlib>

#include<GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "Setup/OpenGLSetup.h"
#include "Shaders/VecterShaderSource.h"
#include "Shaders/FragmentShaderSource.h"


//void framebuffer_size_callback(GLFWwindow * window,int width,int height);
void processInput(GLFWwindow * window);
std::vector<float> processColor(std::vector<float> colorVector);





int main() {

    OpenGLSetup default_setup;
    default_setup.setup();


// build and compile our shader program

    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }



    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //link program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);





 //Vertex data

    //rectangle using EBO
    float vertices[] = {
         0.5f, 0.5f, 0.0f,   // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left

    };

    unsigned int indices[] = {
            0,1,3, //first triangle
            1,2,3  //second triangle
    };



    //Generate Buffer
    unsigned int VBO,VAO,EBO;

    glGenBuffers(1, &VBO);
    glGenBuffers(1,&EBO);
    glGenVertexArrays(1,&VAO);

    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);

    // 2. copy our vertices array in a vertex buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    // 3. copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    // 4. then set the vertex attributes pointers
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);



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

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        glBindVertexArray(0);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


        //check and call events and swap buffers
        glfwPollEvents();
        glfwSwapBuffers(default_setup.window);
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











