#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

class Shader
{
public:
    // program id
    unsigned int ID;

    // default constructor for applying a default shader
    Shader();
    // constructor to apply shaders that user specifies the path to
    Shader(const char *vertexPath, const char *fragmentPath);
    ~Shader();
    // to use or activate the shader
    void use() const;
    void unbind() const;
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setUniform4f(const std::string &name, float r, float g, float b, float a) const;
    void setUniformMat4f(const std::string &name, const glm::mat4 &matrix) const;
    // some helper functions
    unsigned int compileShader(unsigned int type, const std::string &source);
};