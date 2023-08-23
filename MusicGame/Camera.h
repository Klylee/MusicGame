#pragma once

#include "depend.h"


enum ProjectionMode
{
	Perspective, Ortho
};

class Camera
{
private:
	glm::mat4 projection;
	glm::mat4 view;

	void updateProjectionMat();
	void updateViewMat();
public:
	ProjectionMode projMode;
	glm::vec3 position;
	glm::vec3 direct;
	float WHRatio;
	float size;
	float pixelPerUnit;

	float near;
	float far;

	float fieldView;
	float speed;
	
	glm::vec4 backgroundColor;


	Camera(int width, int height);

	glm::mat4 getProjection();
	glm::mat4 getView();

	void setProjectionMode(ProjectionMode m);
	void setSize(float size);
	void setBackgroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	void forward();
	void backward();
	void turnleft();
	void turnright();
	void upward();
	void downward();
};

