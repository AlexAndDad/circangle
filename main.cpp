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

const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";



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
    glewInit();

    //Sets OPENGl viewport and registers callback function to resize it.

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


// build and compile our shader program
    // ------------------------------------
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
    glDeleteShader(vertexShader);
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
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);







    float vertices[] = {
            -0.5f,-0.5f,0.0f,
            0.5f,-0.5f,0.0f,
            0.0f,0.5f,0.0f
    };





    //Generate Buffer
    unsigned int VBO,VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1,&VAO);

    glBindVertexArray(VAO);
    //Bind buffer to Array Buffer
    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    //Copy vertex data into buffer memory
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    std::vector<float> colorVector = {0.0f,0.0f,0.0f,1.0f};
    //Render Loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        //rendering commands

        //colorVector = processColor(colorVector);
        //glClearColor(colorVector[0],colorVector[1],colorVector[2],colorVector[3]);
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);


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











