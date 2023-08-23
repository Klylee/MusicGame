#pragma once

#include "depend.h"
#include "Scene.h"

class MainWindow
{
public:
	GLFWwindow* window;
	int width;
	int height;

	Scene* mainScene;

public:
	MainWindow(int width, int height);
	~MainWindow();

	void mainLoop();
};

glm::u32vec2 getCursorPos();