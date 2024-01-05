#include "Camera.h"


void Camera::updateProjectionMat()
{
	if (projMode == Ortho)
		projection = glm::ortho(-size * WHRatio, size * WHRatio, -size, size, near, far);
	else
		projection = glm::perspective(glm::radians(fieldView), WHRatio, near, far);
}

void Camera::updateViewMat()
{
	view = glm::lookAt(position, glm::vec3(position + direct), glm::vec3(0, 1, 0));
}


Camera::Camera(int width, int height) : WHRatio((float)width / (float)height), size(5), position(0, 0, 10), direct(0, 0, -1), fieldView(45), speed(0.2f), backgroundColor(0)
{
	near = 0.1f;
	far = 100.0f;
	projMode = Ortho;
	pixelPerUnit = size / (height >> 1);
	updateProjectionMat();
	updateViewMat();
}

glm::mat4 Camera::getProjection() const
{
	return projection;
}

glm::mat4 Camera::getView() const
{
	return view;
}

void Camera::setProjectionMode(ProjectionMode m)
{
	ProjectionMode last = projMode;
	projMode = m;
	if (last != projMode)
		updateProjectionMat();
}

void Camera::setSize(float size)
{
	this->size = size;
	updateProjectionMat();
}

void Camera::setBackgroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	backgroundColor = glm::vec4((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, (float)a / 255.0f);
}

void Camera::forward()
{
	glm::vec3 dir_cast(direct.x, 0.0f, direct.z);
	dir_cast = glm::normalize(dir_cast);
	position += dir_cast * speed;
}

void Camera::backward()
{
	glm::vec3 dir_cast(direct.x, 0.0f, direct.z);
	dir_cast = glm::normalize(dir_cast);
	position += -dir_cast * speed;
}

void Camera::turnleft()
{
	glm::vec3 dir_cast(direct.x, 0.0f, direct.z);
	dir_cast = glm::normalize(dir_cast);
	dir_cast = glm::vec3(dir_cast.z, 0.0f, -dir_cast.x);
	position += dir_cast * speed;
}

void Camera::turnright()
{
	glm::vec3 dir_cast(direct.x, 0.0f, direct.z);
	dir_cast = glm::normalize(dir_cast);
	dir_cast = glm::vec3(-dir_cast.z, 0.0f, dir_cast.x);
	position += dir_cast * speed;
}

void Camera::upward()
{
	position.y += speed;
}

void Camera::downward()
{
	position.y -= speed;
}