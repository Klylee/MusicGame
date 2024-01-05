#include "MainWindow.h"
#include "MouseEvent.h"
#include "Time.h"


glm::u32vec2 pos;

MouseButtonEvent* event = nullptr;





void MouseMoveEventHandle(GLFWwindow* window, double xpos, double ypos)
{
    pos.x = xpos;
    pos.y = ypos;
}

void MouseButtonEventHandle(GLFWwindow* window, int button, int act, int modifier)
{
    EventType type = MouseRelease;
    Button b;

    if (act == GLFW_PRESS)
        type = MousePress;
    else if (act == GLFW_RELEASE)
        type = MouseRelease;

    if (button == GLFW_MOUSE_BUTTON_LEFT)
        b = Left;
    else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
        b = Middle;
    else if (button == GLFW_MOUSE_BUTTON_RIGHT)
        b = Right;

    event = new MouseButtonEvent(pos.x, pos.y, type, b);
}

MainWindow::MainWindow(int width, int height)
	: width(width), height(height), mainScene(nullptr)
{
    if (!glfwInit())
        return;

    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    glfwSetMouseButtonCallback(window, MouseButtonEventHandle);
    glfwSetCursorPosCallback(window, MouseMoveEventHandle);
    glfwMakeContextCurrent(window);

    if (glewInit() == GLEW_OK)
        std::cout << "glew init ok" << std::endl;
}

MainWindow::~MainWindow()
{
    glfwTerminate();
}

double Core::frameInterval = 0;
double start;

void MainWindow::mainLoop()
{
    while (!glfwWindowShouldClose(window) && mainScene != nullptr)
    {
        start = glfwGetTime();

        if (event) {
            mainScene->processSelection(window, event);
            delete event;
            event = nullptr;
        }
        //mainScene->checkNullObject();

        mainScene->update();
        mainScene->renderScene(window);
        glfwPollEvents();

        Core::frameInterval = glfwGetTime() - start;
    }
}

glm::u32vec2 getCursorPos()
{
    return pos;
}
