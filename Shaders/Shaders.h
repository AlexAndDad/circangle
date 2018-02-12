//
// Created by ahodges on 12/02/18.
//

#ifndef CIRCANGLE_SHADERS_H
#define CIRCANGLE_SHADERS_H

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shaders
{
public:
    //Program ID:
    unsigned int ID;

    //Constructor reads and builds shader
    Shaders(const GLchar * vertexPath, const GLchar * fragmentPath);

    //use/activate shader
    void use();
    //utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

};


#endif //CIRCANGLE_SHADERS_H
