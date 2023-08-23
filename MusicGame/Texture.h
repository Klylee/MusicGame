#pragma once

#include "depend.h"

enum TextureType
{
    DIFFUSE, SPECULAR, AMBIENT
};

class Texture {
private:
    unsigned int texid;
    TextureType type;

public:
    Texture(const std::string& filepath, TextureType type);
    ~Texture();

    void bind(unsigned int channel) const;
    void unbind() const;

    void deleteTexture();

    Texture& operator=(const Texture& tex);
};