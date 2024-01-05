#pragma once

#include "depend.h"
#include "Camera.h"
#include "Object2D.h"
#include "Square.h"
#include "TextLabel.h"
#include "MouseEvent.h"
#include <vector>
#include <mutex>


class Scene : public Object2D
{
	int width;
	int height;
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
	void update();


	Vector3 screenPostoWorldPos(int x, int y, float z);
};

inline void Scene::update()
{
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->update();
	}
}

inline Vector3 Scene::screenPostoWorldPos(int x, int y, float z)
{
	float wy = camera.pixelPerUnit * ((float)height / 2.0f - (float)y);
	float wx = camera.pixelPerUnit * (float)x - camera.size * camera.WHRatio;
	return Vector3(wx, wy, z);
}
