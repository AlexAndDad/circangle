//
// Created by ahodges on 11/02/18.
//

#include "VecterShaderSource.h"


const char * vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n" //Position variable has attribute position 0
        "layout (location = 1) in vec3 aColor;\n"

        "out vec3 ourColor;\n"

        "void main()\n"
        "{\n"

        "   gl_Position = vec4(aPos,1.0);\n"
        "   ourColor = aColor;\n"

        "}\0";