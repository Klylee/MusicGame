#pragma once
#include "depend.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Transform.h"
#include "MouseEvent.h"
#include <vector>
#include <functional>
#include "Object2D.h"

class Square : public Object2D
{
private:
	unsigned int vao;
	unsigned int vbo;
	unsigned int ibo;

	typedef std::function<void(std::string)> EventFunc;
	std::vector<EventFunc> callbacks;
	

public:
	Texture* texture;
	Shader* shader;
	Shader* colorCodeShader;
	Color color;
	float textureTransparency;

	explicit Square(Object2D* parent = nullptr);

	~Square();

	void renderSelect(Camera& camera, int code) const override;
	void draw(Camera& camera) const override;


	void setCallback(const EventFunc& func);
	void mouseEvent(MouseButtonEvent* e);
	void onMouseRelease(MouseButtonEvent* e);
	void onMousePress(MouseButtonEvent* e);
};