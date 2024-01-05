#pragma once

#include "Shader.h"
#include "Texture.h"
#include <vector>

class Geometry
{
	unsigned int vao;
	unsigned int vbo;
	unsigned int ibo;

	unsigned int modelMatBuffer;
public:
	Shader* shader;
	Texture* texture;

	std::vector<glm::mat4> modelMats;

	bool instance;
	glm::vec2 translations;

public:
	explicit Geometry(float* vertices, unsigned int* indices);
	~Geometry();
	void draw();
};

