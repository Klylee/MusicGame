#pragma once

#include "Square.h"
#include "depend.h"
#include "Shader.h"
#include "CharTexture.h"
#include "Time.h"
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


namespace UI {
	class TextLabel : public Object2D
	{
	public:
		void renderColorCodeMap(const Camera& camera, int code) const override {}
		void draw(const Camera& camera) const override;
		TextLabel(unsigned int fontSize, const std::string& fontfile, const std::string& text = "New Text", Object2D* parent = nullptr);
		~TextLabel();
		inline void setTextColor(const Color& color)
		{
			textColor = color;
		}
		void setText(std::string s);

		void update();

	private:
		std::string text;
		std::vector<CharTexture*> texttexs;
		std::string font;
		int fontSize;
		Color textColor;
		glm::ivec2 bearing;
		unsigned int advance;

		unsigned int vao;
		unsigned int vbo;
		unsigned int ibo;

	public:
		static CharTexturesMap chartexmap;
		Core::Time timer;

		Shader* shader;
	};
}
