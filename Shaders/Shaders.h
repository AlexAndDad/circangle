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
#include <boost/filesystem.hpp>

class Shaders
{
private:
    struct internal_flag {};
    Shaders(internal_flag, const GLchar * vertexPath, const GLchar * fragmentPath);
public:

    using path = boost::filesystem::path;

    //Program ID:
    unsigned int ID;

    // static root path for finding shaders
    static path shader_root_;

    //Constructor reads and builds shader
    Shaders(path const& vertexPath, path const& fragmentPath);

    //use/activate shader
    void use();
    //utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

    static void deduceRoot(boost::filesystem::path const& programPath);
    static auto fixPath(path arg) -> path;

};


#endif //CIRCANGLE_SHADERS_H
