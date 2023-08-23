#include "Shader.h"
#include <cassert>


ShaderSourceString Shader::PraseShaderSource(const std::string& file)
{
    std::ifstream source(file);
    if (!source.is_open())
    {
        std::cout << "the given file path maybe wrong" << std::endl;
        return {};
    }

    std::string vertex_source;
    std::string fragment_source;
    int type = -1; //specifies the shader mode
    std::string line;
    while (getline(source, line))
    {
        if (line.find("#shader") != std::string::npos) //need to prase
        {
            if (line.find("vertex") != std::string::npos)
                type = 0;
            else if (line.find("fragment") != std::string::npos)
                type = 1;
        }
        else { //start prase
            if (type == 0) //vertex mode
            {
                vertex_source += line;
                vertex_source += "\n";
            }
            else if (type == 1) //fragment mode
            {
                fragment_source += line;
                fragment_source += "\n";
            }
        }
    }
    return { vertex_source, fragment_source };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& shader_source)
{
    unsigned int shader;
    //before create shader, we need to check if the type given is right
    if (type != GL_VERTEX_SHADER && type != GL_FRAGMENT_SHADER)
    {
        std::cout << "give the wrong type of shader" << std::endl;
        return 0;
    }

    shader = glCreateShader(type);
    const char* c_src = shader_source.c_str();
    glShaderSource(shader, 1, &c_src, NULL);
    glCompileShader(shader);

    //check if compiling successfully
    int res;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &res);
    if (res == GL_FALSE)
    {
        int len;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
        char* info = new char[len];
        glGetShaderInfoLog(shader, len, &len, info);
        std::cout << info << std::endl;
        delete[] info;
    }
    return shader;
}

int Shader::getUnifromLocation(const std::string& label) const
{
    int loc = glGetUniformLocation(program, label.c_str());
    if (loc == -1) {
        std::cout << "get uniform location fail: \"" << label << "\"" << std::endl;
        return -1;
    }
    //std::cout << "\"" << label << "\" location: " << loc << std::endl;
    return loc;
}

Shader::Shader(const std::string& shaderpath) {
    ShaderSourceString ss = PraseShaderSource(shaderpath);

    program = glCreateProgram();
    unsigned int vertex_shader = CompileShader(GL_VERTEX_SHADER, ss.vertex_source);
    unsigned int fragment_shader = CompileShader(GL_FRAGMENT_SHADER, ss.fragment_source);

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program); //link the two shader together
    glValidateProgram(program); //validate the program

    glDeleteShader(vertex_shader); //now we don't need the shader object
    glDeleteShader(fragment_shader);
}

Shader::~Shader()
{
    glDeleteProgram(program);
}

void Shader::useprogram() const 
{
    glUseProgram(program);
}

void Shader::deleteprogram() {
    glDeleteProgram(program);
}

void Shader::setUniform1f(const std::string& label, float v) const
{
    int loc = getUnifromLocation(label);
    if (loc >= 0)
        glUniform1f(loc, v);
}

void Shader::setUniform1i(const std::string& label, int v) const
{
    int loc = getUnifromLocation(label);
    if (loc >= 0)
        glUniform1i(loc, v);
}

void Shader::setUniformVec3f(const std::string& label, float v1, float v2, float v3) const
{
    int loc = getUnifromLocation(label);
    if(loc >= 0)
        glUniform3f(loc, v1, v2, v3);
}

void Shader::setUniformVec3i(const std::string& label, int v1, int v2, int v3) const
{
    int loc = getUnifromLocation(label);
    if (loc >= 0)
        glUniform3i(loc, v1, v2, v3);
}

void Shader::setUniformVec4f(const std::string& label, float v1, float v2, float v3, float v4) const
{
    int loc = getUnifromLocation(label);
    if (loc >= 0)
        glUniform4f(loc, v1, v2, v3, v4);
}

void Shader::setUniformVec4i(const std::string& label, int v1, int v2, int v3, int v4) const
{
    int loc = getUnifromLocation(label);
    if (loc >= 0)
        glUniform4i(loc, v1, v2, v3, v4);
}

void Shader::setUniformMat4x4f(const std::string& label, int matCount, const float* value) const
{
    int loc = getUnifromLocation(label);
    if (loc >= 0)
        glUniformMatrix4fv(loc, matCount, GL_FALSE, value);
}
