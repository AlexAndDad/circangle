#include <cstdlib>

#include<GL/glew.h>
#include <glm/glm.hpp>

#if __has_include(<OpenGL/gl.h>)
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif

#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <tgmath.h>

#include "Setup/OpenGLSetup.h"
#include "Shaders/Shaders.h"
#include <boost/filesystem.hpp>
#include "stb/stb_image.h"
#include "Resources/ResourceService.hpp"


//void framebuffer_size_callback(GLFWwindow * window,int width,int height);
void processInput(GLFWwindow *window);
//std::vector<float> processColor(std::vector<float> colorVector);


extern ResourceService resources;


int main(int argc, const char *argv[])
{
    resourceService().deduceRoot(argv[0]);

    OpenGLSetup default_setup;
    default_setup.setup();


// build and compile our shader program

    Shaders ourShader("VertexShader.glsl", "FragmentShader.glsl");


    //-----------------------------------------------------------------------

    stbi_set_flip_vertically_on_load(true);

    //Generate texture ID -1
    unsigned int texture;
    glGenTextures(1, &texture);

    //Bind texture
    glBindTexture(GL_TEXTURE_2D, texture);


    //Load texture from file
    int width, height, nrChannels;
    unsigned char *data = stbi_load((resourceService().root() / "Textures/container.jpg").c_str(), &width, &height,
                                    &nrChannels, 0);
    if (data) {
        //Generate texture using previously loaded data
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    //Free image data memory
    stbi_image_free(data);

    //------------------------------

    //Generate texture ID -2
    unsigned int texture1;
    glGenTextures(1, &texture1);

    //Bind texture
    glBindTexture(GL_TEXTURE_2D, texture1);



    //Load texture from file

    data = stbi_load((resourceService().root() / "Textures/awesomeface.png").c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        //Generate texture using previously loaded data
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    //Free image data memory
    stbi_image_free(data);







    //-----------------------------------------------------------------------

    float vertices[] = {
        //Positions            //colors             //Texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };



    //Generate buffers for vertices0
    unsigned int VAO, VBO, EBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    //Bind vertex array object
    glBindVertexArray(VAO);

    //Bind Vertex buffer object, declare data.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Bind Element buffer object, declare data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    //Set vertex attribute pointers for vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);

    //Set vertex attribute pointer for colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //-----------------------------------------------------------------------------------


    //Background color vector init;
    std::vector<float> colorVector = {0.0f, 0.0f, 0.0f, 1.0f};



    //Render Loop
    while (!glfwWindowShouldClose(default_setup.window)) {
        // input
        processInput(default_setup.window);

        //rendering commands

        //colorVector = processColor(colorVector);
        //glClearColor(colorVector[0],colorVector[1],colorVector[2],colorVector[3]);
        glClearColor(0.3f, 0.3f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        ourShader.use();
        ourShader.setInt("texture1", 0);
        ourShader.setInt("texture2", 1);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


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

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
/*std::vector<float> processColor(std::vector<float> colorVector)
{
    float r =  ((float)rand() / RAND_MAX);
    float g =  ((float)rand() / RAND_MAX);
    float b =  ((float)rand() / RAND_MAX);

    colorVector[0] = r;
    colorVector[1] = g;
    colorVector[2] = b;
    return colorVector;
}
*/










