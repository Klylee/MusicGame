#include "Application.h"


Application::Application(MainWindow& window)
    : mainScene(nullptr)
{
    mainScene = new Scene(window.width, window.height);
    mainScene->camera.setBackgroundColor(24, 24, 82, 255);

    Square* square = new Square;
    square->shader = assetsManager.loadShader(std::string(ROOT_PATH) + "assets/Shaders/ui.shader");
    square->colorCodeShader = assetsManager.loadShader(std::string(ROOT_PATH) + "assets/Shaders/ColorCode.shader");
    square->texture = assetsManager.loadTexture(std::string(ROOT_PATH) + "assets/textures/star.png");

    square->color = Color(240, 233, 249, 255);
    square->textureTransparency = 0.0f;
    square->transform.scale(Vector3(2.0f, 1.0f, 1.0f));
    square->transform.position(Vector3(1.0f, 0, 0));
    square->setCallback(std::bind(&Application::on_Square_Clicked, this, std::placeholders::_1));
    square->setCallback(std::bind(&Application::func, this, std::placeholders::_1));

    mainScene->addObject(square);

    /*TextLabel* textlabel = new TextLabel(40, "./xxx.ttf", Color(219, 202, 239, 255), "abcdefgFG");
    textlabel->shader = assetsManager.loadShader(std::string(ROOT_PATH) + "assets/Shaders/text.shader");
    mainScene->addObject(textlabel);*/
}

Application::~Application()
{
    if (mainScene)
        delete mainScene;
}



void Application::on_Square_Clicked(std::string e)
{
    std::cout << "square1" << std::endl;
}
void Application::func(std::string e)
{
    for (int i = 0; i < 1000; i++) {
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

        TextLabel* textlabel = new TextLabel(40, "./xxx.ttf", "abcdefgFG");
        textlabel->shader = assetsManager.loadShader(std::string(ROOT_PATH) + "assets/Shaders/text.shader");
        textlabel->setTextColor(Color(219, 202, 239, 255));
        mainScene->addObject(textlabel);

        mainScene->destroy(textlabel, 1000);
    }
}