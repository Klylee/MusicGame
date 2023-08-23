#pragma once

#include "Object2D.h"
#include "depend.h"
#include "Shader.h"
#include "CharTexture.h"
#include <map>


class CharTexturesMap
{
	std::map<std::string, std::map<char, std::map<unsigned int, CharTexture*>>> charTexturesMap;

public:
	CharTexturesMap() {}
	~CharTexturesMap();
	

	CharTexture* loadCharTexture(char c, unsigned int fontsize);
	CharTexture* findCharTexture(const std::string& font, const char c, const unsigned int fontsize);
};


class TextLabel : public Object2D
{
public:
	TextLabel(unsigned int fontSize, const std::string& fontfile, const std::string& text = "New Text", Object2D* parent = nullptr);
	~TextLabel();

	void renderSelect(Camera& camera, int code) const override;
	void draw(Camera& camera) const override;
	inline void setTextColor(const Color& color)
	{
		textColor = color;
	}

private:
	std::string text;
	CharTexture** texttexs;
	std::string font;
	int fontSize;
	Color textColor;
	glm::ivec2 bearing;
	unsigned int advance;

	unsigned int vao;
	unsigned int vbo;
	unsigned int ibo;

public:
	Shader* shader;
	static CharTexturesMap chartexmap;
};
