#pragma once

#include "MainWindow.h"
#include "AssetsManager.h"
#include "Scene.h"

class Application
{
	AssetsManager assetsManager;
public:
	Scene* mainScene;

public:
	explicit Application(MainWindow& window);
	~Application();

	void on_Square_Clicked(std::string e);
	void func(std::string e);
};