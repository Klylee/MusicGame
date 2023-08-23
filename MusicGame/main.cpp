#include "depend.h"
#include "Application.h"
#include "MainWindow.h"
#include <Windows.h>



int main()
{
    MainWindow window(1000, 800);

    Application app(window);

    /*Square* square2 = new Square;
    square2->transform.position(Vector3(1.0f, -2.0f, 0));
    square2->color = Color(240, 233, 178, 255);
    square2->textureTransparency = 0.0f;
    square2->transform.scale(Vector3(2.0f, 1.0f, 1.0f));
    square2->setTexutre(std::string(ROOT_PATH) + "assets/textures/grid2.png");
    square2->setCallback(on_Square2_Clicked);

    mainScene->addObject(square2);*/

    
    window.mainScene = app.mainScene;

    window.mainLoop();
    return 0;
}