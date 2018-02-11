//
// Created by ahodges on 11/02/18.
//

#ifndef CIRCANGLE_OPENGLSETUP_H
#define CIRCANGLE_OPENGLSETUP_H
#include <cstdlib>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

struct OpenGLSetup {

    OpenGLSetup()
    {};

    void setup();
    void glfw_Setup();
    void screen_Resolution_Setup();
    void window_Init();
    void init_GLEW();
    void define_Callbacks();



    int SCR_WIDTH = 0;
    int SCR_HEIGHT = 0;

    GLFWwindow * window;

};

inline void framebuffer_size_callback(GLFWwindow * window,int width,int height)
{
    glViewport(0,0,width,height);
}



#endif //CIRCANGLE_OPENGLSETUP_H
