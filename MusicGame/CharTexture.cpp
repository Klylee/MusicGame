#include "CharTexture.h"


CharTexture::CharTexture(const FT_Face& face)
    : size(face->glyph->bitmap.width, face->glyph->bitmap.rows),
    bearing(face->glyph->bitmap_left, face->glyph->bitmap_top),
    advancex(face->glyph->advance.x)
{
    glGenTextures(1, &_texid);
    glBindTexture(GL_TEXTURE_2D, _texid);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

CharTexture::~CharTexture()
{
    glDeleteTextures(1, &_texid);
}

void CharTexture::bind(unsigned int channel)
{
    glActiveTexture(GL_TEXTURE0 + channel);
    glBindTexture(GL_TEXTURE_2D, _texid);
}

void CharTexture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}