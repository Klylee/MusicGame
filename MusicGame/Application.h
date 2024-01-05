#pragma once

#include "MainWindow.h"
#include "Note.h"
#include "AssetsManager.h"
#include "GameManager.h"
#include "Scene.h"
#include <queue>



class Application
{

public:
	Scene* mainScene;

	Note* notePrefab;
	GameManager* gameManager;

public:
	explicit Application(MainWindow& window);
	~Application();

	void on_Square_Clicked(std::string e);
	void func(std::string e);
	void loadTracks();
};
