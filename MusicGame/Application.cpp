#include "Application.h"
#include "Button.h"
#include "TextLabel.h"


Application::Application(MainWindow& window)
    : mainScene(nullptr)
{
    mainScene = new Scene(window.width, window.height);
    mainScene->camera.setBackgroundColor(24, 24, 82, 255);


    UI::Button* button = new UI::Button(mainScene);
    button->shader = assetsManager.loadShader(std::string(ROOT_PATH) + "assets/Shaders/ui.shader");
    button->texture = assetsManager.loadTexture(std::string(ROOT_PATH) + "assets/textures/star.png");
    button->color = Color(240, 233, 249, 255);
    button->textureTransparency = 0.0f;
    button->transform.scale(Vector3(2.0f, 1.0f, 1.0f));
    button->transform.position(Vector3(2.0f, 0, 0));
    button->setCallback(std::bind(&Application::on_Square_Clicked, this, std::placeholders::_1));
    button->setCallback(std::bind(&Application::func, this, std::placeholders::_1));

    mainScene->addObject(button);

    notePrefab = new Note(mainScene);
    notePrefab->shader = assetsManager.loadShader(std::string(ROOT_PATH) + "assets/Shaders/ui.shader");
    notePrefab->texture = assetsManager.loadTexture(std::string(ROOT_PATH) + "assets/textures/otto.png");
    notePrefab->color = Color(180, 179, 255, 255);
    notePrefab->textureTransparency = 0.0f;
    notePrefab->setDestroyDelegate(std::bind(&Scene::destroy, mainScene, std::placeholders::_1, std::placeholders::_2));

    /*Square* sq = new Square(mainScene);
    sq->shader = assetsManager.loadShader(std::string(ROOT_PATH) + "assets/Shaders/ui.shader");
    sq->transform.position(mainScene->screenPostoWorldPos(300, 500, 0));
    mainScene->addObject(sq);*/

    UI::TextLabel* textlabel = new UI::TextLabel(40, "./xxx.ttf", "abcdefgFG", mainScene);
    textlabel->setTextColor(Color(219, 202, 239, 255));
    textlabel->shader = assetsManager.loadShader(std::string(ROOT_PATH) + "assets/Shaders/text.shader");
    textlabel->transform.position(mainScene->screenPostoWorldPos(10, 50, 0));
    mainScene->addObject(textlabel);

    gameManager = new GameManager;
    loadTracks();
    mainScene->addObject(gameManager);
    gameManager->setDestroyDelegate(std::bind(&Scene::destroy, mainScene, std::placeholders::_1, std::placeholders::_2));
}

Application::~Application()
{
    if (mainScene)
        delete mainScene;

    delete notePrefab;
}



void Application::on_Square_Clicked(std::string e)
{
    std::cout << "square1" << std::endl;
}
void Application::func(std::string e)
{
        /*Square* square = new Square;
        if (square == nullptr) {
            std::cout << "error-----------" << std::endl;
            return;
        }
        square->shader = assetsManager.loadShader(std::string(ROOT_PATH) + "assets/Shaders/ui.shader");
        square->colorCodeShader = assetsManager.loadShader(std::string(ROOT_PATH) + "assets/Shaders/ColorCode.shader");
        square->texture = assetsManager.loadTexture(std::string(ROOT_PATH) + "assets/textures/star.png");

        square->color = Color(240, 233, 249, 255);
        square->textureTransparency = 0.0f;
        square->transform.scale(Vector3(2));
        square->transform.position(Vector3(-1.0f, 0, 0));
        mainScene->addObject(square);*/

        /*TextLabel* textlabel = new TextLabel(40, "./xxx.ttf", "abcdefgFG");
        textlabel->shader = assetsManager.loadShader(std::string(ROOT_PATH) + "assets/Shaders/text.shader");
        textlabel->setTextColor(Color(219, 202, 239, 255));
        mainScene->addObject(textlabel);*/

    Note* note = notePrefab->duplicate();
    mainScene->addObject(note);
    note->transform.position(Vector3(-0.5f, 6.0f, 0));
    note->active = false;

    /*mainScene->destroy(note, 10000);*/
}

void Application::loadTracks()
{
    // std::ifstream trackFile(std::string(ROOT_PATH) + "assets/GameSources/music1.trac");
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 4; j++) {
            Note* note = notePrefab->duplicate();
            mainScene->addObject(note);
            note->transform.position(mainScene->screenPostoWorldPos(200 + j * 100, 0 - i * 100 - j * 25, 0));
            note->active = false;
            gameManager->tracks[j].push(note);
        }                       
    }
}
