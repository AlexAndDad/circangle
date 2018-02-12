//
// Created by ahodges on 12/02/18.
//

#include "Shaders.h"


Shaders::Shaders(const GLchar * vertexPath, const GLchar * fragmentPath)
{
    //1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    //ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        //open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        //read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        //close file handlers
        vShaderFile.close();
        fShaderFile.close();

        //convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADERS::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char * vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();


    //2. compile shaders
    unsigned int vertex, fragment;
    int success;
    std::string result;
    GLint length = 0;

    //vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex,1,&vShaderCode,nullptr);
    glCompileShader(vertex);
    //print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {

        glGetShaderiv(vertex,GL_INFO_LOG_LENGTH,&length);
        result = std::string(length,'\0');

        glGetShaderInfoLog(vertex,length,nullptr,result.data());
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << result << std::endl;

    }


    //Fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1,&fShaderCode,nullptr);
    glCompileShader(fragment);
    //print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderiv(fragment,GL_INFO_LOG_LENGTH,&length);
        result = std::string(length,'\0');

        glGetShaderInfoLog(fragment,length,nullptr,result.data());
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << result << std::endl;
    };


    //Shader program
    ID = glCreateProgram();
    glAttachShader(ID,vertex);
    glAttachShader(ID,fragment);
    glLinkProgram(ID);
    //Print linking errors
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramiv(ID,GL_INFO_LOG_LENGTH,&length);
        result = std::string(length,'\0');

        glGetProgramInfoLog(ID, length, nullptr, result.data());
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << result << std::endl;
    }

    //delete the shaders as they're linked into the program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shaders::use()
{
    glUseProgram(ID);
}

void Shaders::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID,name.c_str()),int(value));
}
void Shaders::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID,name.c_str()),value);
}
void Shaders::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID,name.c_str()),value);
}