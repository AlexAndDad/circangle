//
// Created by ahodges on 11/02/18.
//

#include "FragmentShaderSource.h"


const char *fragmentShaderSource = "#version 330 core\n"

        "out vec4 FragColor;\n"
        "in vec3 ourColor;\n"

        "void main()\n"
        "{\n"
        "   FragColor = vec4(ourColor,1.0);\n"
        "}\n\0";