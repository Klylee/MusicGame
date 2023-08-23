#pragma once

#include "depend.h"
#include <fstream>

struct ShaderSourceString {
    std::string vertex_source;
    std::string fragment_source;
};


class Shader
{
    ShaderSourceString PraseShaderSource(const std::string& file);
    unsigned int CompileShader(unsigned int type, const std::string& shader_source);
    
    int getUnifromLocation(const std::string& label) const;
public:
    unsigned int program;


    Shader(const std::string& shaderpath);
    ~Shader();

    void useprogram() const;
    void deleteprogram();

    void setUniform1f(const std::string& label, float v) const;
    void setUniform1i(const std::string& label, int v) const;
    void setUniformVec3f(const std::string& label, float v1, float v2, float v3) const;
    void setUniformVec3i(const std::string& label, int v1, int v2, int v3) const;
    void setUniformVec4f(const std::string& label, float v1, float v2, float v3, float v4) const;
    void setUniformVec4i(const std::string& label, int v1, int v2, int v3, int v4) const;
    void setUniformMat4x4f(const std::string& label, int matCount, const float* value) const;
};

