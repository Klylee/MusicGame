#pragma once

#include "depend.h"
#include "Camera.h"
#include "Object2D.h"
#include "Square.h"
#include "TextLabel.h"
#include "MouseEvent.h"
#include <vector>
#include <mutex>

class Scene
{
public:
	std::mutex _mutex;

	Camera camera;
	std::vector<Object2D*> objects;

	explicit Scene(int w, int h);
	~Scene();
	void addObject(Object2D* object);
	void destroy(Object2D* object, float timelapse);

	void renderScene(GLFWwindow* window);
	void processSelection(GLFWwindow* window, MouseButtonEvent* e);
};