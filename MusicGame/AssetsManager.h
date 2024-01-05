#pragma once

#include "Shader.h"
#include "Texture.h"
#include "CharTexture.h"
#include <map>
#include <string>


class AssetsManager
{
	std::map<std::string, Shader*> shadersMap;
	std::map<std::string, Texture*> texturesMap;

public:
	explicit AssetsManager() {}
	~AssetsManager();

	Shader* findShader(const std::string& shaderName);
	Texture* findTexture(const std::string& textureName);

	Shader* loadShader(const std::string& shaderfile);
	Texture* loadTexture(const std::string& texturefile);

	void deleteShader(const std::string& shaderName);
	void deleteTexture(const std::string& textureName);
};

extern AssetsManager assetsManager;