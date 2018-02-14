//
// Created by ahodges on 11/02/18.
//

#include "OpenGLSetup.h"

//Main function
void OpenGLSetup::setup()
{
    glfw_Setup();
    screen_Resolution_Setup();
    window_Init();
    init_GLEW();
    define_Callbacks();

}

//Setup glfw profile
void OpenGLSetup::glfw_Setup()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    #endif
}

//Detect and set video resolution
void OpenGLSetup::screen_Resolution_Setup()
{
    SCR_WIDTH  = glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
    SCR_HEIGHT = glfwGetVideoMode(glfwGetPrimaryMonitor())->height;
}

//Create window object and check if it initialised correctly.
void OpenGLSetup::window_Init()
{
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOPenGlMofo", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window";
        glfwTerminate();
    }
    else {
        glfwMakeContextCurrent(window);
    }
}

//
void OpenGLSetup::init_GLEW()
{
    glewInit();


}

//Defines Callbacks.
void OpenGLSetup::define_Callbacks()
{
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

}