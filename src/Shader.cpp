#include "Shader.h"
#include "Renderer.h"

Shader::Shader()
{

    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // ensure that ifstream objects can throw exception
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open("../resources/shaders/basic.vs");
        fShaderFile.open("../resources/shaders/basic.fs");
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into stream
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert the streams into strings
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::istream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCEFULLY_READ";
    }

    unsigned int vertex = compileShader(GL_VERTEX_SHADER, vertexCode);
    unsigned int fragment = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

    // create the shaders
    GlCall(ID = glCreateProgram());
    GlCall(glAttachShader(ID, vertex));
    GlCall(glAttachShader(ID, fragment));
    GlCall(glLinkProgram(ID));
    GlCall(glValidateProgram(ID));

    GlCall(glDeleteShader(vertex));
    GlCall(glDeleteShader(fragment));
}

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // ensure that ifstream objects can throw exception
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into stream
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert the streams into strings
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::istream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCEFULLY_READ";
    }

    unsigned int vertex = compileShader(GL_VERTEX_SHADER, vertexCode);
    unsigned int fragment = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

    // create the shaders
    GlCall(ID = glCreateProgram());
    GlCall(glAttachShader(ID, vertex));
    GlCall(glAttachShader(ID, fragment));
    GlCall(glLinkProgram(ID));
    GlCall(glValidateProgram(ID));
    GlCall(glDeleteShader(vertex));
    GlCall(glDeleteShader(fragment));
}

unsigned int Shader::compileShader(unsigned int type, const std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    GlCall(glShaderSource(id, 1, &src, nullptr));
    GlCall(glCompileShader(id));

    int result;
    GlCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = new char[length];
        glGetShaderInfoLog(id, length, &length, message);
        const char *shadertype = (type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment";
        std::cout << "Error: Failed to compile " << shadertype << " shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        delete[] message;
        return 0;
    }
    return id;
}

Shader::~Shader()
{
    GlCall(glDeleteProgram(ID));
}

void Shader::use() const
{
    GlCall(glUseProgram(ID));
}

void Shader::unbind() const
{
    GlCall(glUseProgram(0));
}

void Shader::setBool(const std::string &name, bool value) const
{
    GlCall(int location = glGetUniformLocation(ID, name.c_str()));
    ASSERT(location != -1);
    GlCall(glUniform1f(location, value));
}

void Shader::setInt(const std::string &name, int value) const
{
    GlCall(int location = glGetUniformLocation(ID, name.c_str()));
    ASSERT(location != -1);
    GlCall(glUniform1i(location, value));
}

void Shader::setFloat(const std::string &name, float value) const
{
    GlCall(int location = glGetUniformLocation(ID, name.c_str()));
    ASSERT(location != -1);
    GlCall(glUniform1f(location, value));
}

void Shader::setUniform4f(const std::string &name, float r, float g, float b, float a) const
{
    GlCall(int location = glGetUniformLocation(ID, name.c_str()));
    ASSERT(location != -1);
    GlCall(glUniform4f(location, r, g, b, a));
}

void Shader::setUniformMat4f(const std::string &name, const glm::mat4 &matrix) const
{
    GlCall(int location = glGetUniformLocation(ID, name.c_str()));
    ASSERT(location != -1);
    GlCall(glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]));
}