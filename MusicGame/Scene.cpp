#include "Scene.h"
#include <thread>
#include <Windows.h>
#include "Button.h"

Scene::Scene(int w, int h) : Object2D(nullptr), width(w), height(h), camera(w, h)
{
}

Scene::~Scene()
{
    for (int i = 0; i < objects.size(); i++)
        if (objects[i] != nullptr)
            delete objects[i];
}

void Scene::addObject(Object2D* object)
{
	objects.push_back(object);
}

void destroyThread(Scene* self, Object2D* obj, float timelapse)
{
    Sleep(timelapse);
    self->_mutex.lock();
    for (auto it = self->objects.begin(); it != self->objects.end(); it++) {
        if (*it == obj) {
            if (obj->getType() == "Square") {
                Square* ptr = (Square*)(obj);
                delete ptr;
            }
            else if (obj->getType() == "TextLabel") {
                UI::TextLabel* ptr = (UI::TextLabel*)(obj);
                delete ptr;
            }
            self->objects.erase(it);
            break;
        }
    }
    self->_mutex.unlock();
}

void Scene::destroy(Object2D* obj, float timelapse)
{
    if (obj == nullptr)
        return;
    
    std::thread t(destroyThread, this, obj, timelapse);
    t.detach();
}

void Scene::renderScene(GLFWwindow* window)
{
    _mutex.lock();

    glClearColor(camera.backgroundColor.r, camera.backgroundColor.g, camera.backgroundColor.b, camera.backgroundColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < objects.size(); i++) {
        if (objects[i]->active)
            objects[i]->draw(camera);
    }

    _mutex.unlock();

	glfwSwapBuffers(window);
}

void Scene::processSelection(GLFWwindow* window, MouseButtonEvent* e)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < objects.size(); i++) {
        if (objects[i]->active && objects[i]->eventSate())
            objects[i]->renderColorCodeMap(camera, i + 1);
    }

    unsigned char color[4];
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glReadPixels(e->position.x, viewport[3] - e->position.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &color);
    
    if (color[0] > 0 && color[0] < objects.size() + 1) {
        if (objects[color[0] - 1]->getType() == "UI") {
            UI::Button* uiobj = (UI::Button*)(objects[color[0] - 1]);
            uiobj->mouseEvent(e);
        }
    }
            
}

