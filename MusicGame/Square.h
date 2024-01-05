#pragma once
#include "depend.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Transform.h"
#include <vector>
#include "Object2D.h"



class Square : public Object2D
{
protected:
	unsigned int vao;
	unsigned int vbo;
	unsigned int ibo;

public:
	void draw(const Camera& camera) const override;
	Texture* texture;
	Shader* shader;
	Color color;
	float textureTransparency;


	Square(Object2D* parent);
	Square(const Square& s);
	~Square();

	
	Square* duplicate();
	void update() override;
};