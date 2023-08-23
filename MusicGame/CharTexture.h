#pragma once

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

class CharTexture
{
public:
	CharTexture(const FT_Face& face);
	~CharTexture();
	
	void bind(unsigned int channel);
	void unbind();

	inline unsigned int texid() const
	{
		return _texid;
	}

	glm::ivec2 size;
	glm::ivec2 bearing;
	int advancex;
private:
	unsigned int _texid;
};