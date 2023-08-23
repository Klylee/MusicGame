#include "AssetsManager.h"

AssetsManager::~AssetsManager()
{
    for (auto i = shadersMap.begin(); i != shadersMap.end(); i++) {
        if (i->second) {
            delete i->second;
        }
    }
    for (auto i = texturesMap.begin(); i != texturesMap.end(); i++) {
        if (i->second) {
            delete i->second;
        }
    }
}

void AssetsManager::deleteShader(const std::string& shaderName)
{
    auto it = shadersMap.find(shaderName);
    if (it != shadersMap.end()) {
        delete it->second;
        shadersMap.erase(it);
    }
}

void AssetsManager::deleteTexture(const std::string& textureName)
{
    auto it = texturesMap.find(textureName);
    if (it != texturesMap.end()) {
        delete it->second;
        texturesMap.erase(it);
    }
}

Shader* AssetsManager::findShader(const std::string& shaderName)
{
    auto it = shadersMap.find(shaderName);
    if(it == shadersMap.end())
        return nullptr;

    return it->second;
}

Texture* AssetsManager::findTexture(const std::string& textureName)
{
    auto it = texturesMap.find(textureName);
    if (it == texturesMap.end())
        return nullptr;

    return it->second;
}

Shader* AssetsManager::loadShader(const std::string& shaderfile)
{
    std::string shaderName = shaderfile.substr(shaderfile.find_last_of("/") + 1);
    shaderName = shaderName.substr(0, shaderName.find_last_of("."));

    Shader* shader = findShader(shaderName);
    if (shader == nullptr) {
        shader = new Shader(shaderfile);
        shadersMap.insert(std::pair<std::string, Shader*>(shaderName, shader));
    }

    return shader;
}

Texture* AssetsManager::loadTexture(const std::string& texturefile)
{
    std::string textureName = texturefile.substr(texturefile.find_last_of("/") + 1);
    textureName = textureName.substr(0, textureName.find_last_of("."));

    Texture* texture = findTexture(textureName);
    if (texture == nullptr) {
        texture = new Texture(texturefile, DIFFUSE);
        texturesMap.insert(std::pair<std::string, Texture*>(textureName, texture));
    }

    return texture;
}
