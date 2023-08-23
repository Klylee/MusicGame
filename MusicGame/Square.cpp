#include "Square.h"

Square::Square(Object2D* parent)
	: Object2D(parent, "Square"), color(255), textureTransparency(1), texture(nullptr), shader(nullptr), colorCodeShader(nullptr)
{
	enableEvent();

	float w = width();
	float h = height();
	glm::vec3 v[4] = {
		glm::vec3(-w / 2, h / 2, 0),
		glm::vec3(w / 2, h / 2, 0),
		glm::vec3(w / 2, -h / 2, 0),
		glm::vec3(-w / 2, -h / 2, 0)
	};

	float vertexBuffer[20];
	for (int i = 0; i < 4; i++) {
		vertexBuffer[i * 5] = v[i].x;
		vertexBuffer[i * 5 + 1] = v[i].y;
		vertexBuffer[i * 5 + 2] = v[i].z;
	}
	vertexBuffer[3] = 0;
	vertexBuffer[4] = 1;
	vertexBuffer[8] = 1;
	vertexBuffer[9] = 1;
	vertexBuffer[13] = 1;
	vertexBuffer[14] = 0;
	vertexBuffer[18] = 0;
	vertexBuffer[19] = 0;

	unsigned int indexBuffer[6] = {
		0, 1, 2,
		0, 2, 3
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(float), vertexBuffer, GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(float), indexBuffer, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)(3 * sizeof(float)));
}

Square::~Square()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Square::renderSelect(Camera& camera, int code) const
{
	colorCodeShader->useprogram();
	colorCodeShader->setUniformMat4x4f("_projection", 1, glm::value_ptr(camera.getProjection()));
	colorCodeShader->setUniformMat4x4f("_view", 1, glm::value_ptr(camera.getView()));
	colorCodeShader->setUniformMat4x4f("_model", 1, glm::value_ptr(transform.localToWorld()));
	colorCodeShader->setUniform1i("_code", code);

	glDisable(GL_BLEND);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}

void Square::draw(Camera& camera) const
{
	shader->useprogram();

	shader->setUniformMat4x4f("_projection", 1, glm::value_ptr(camera.getProjection()));
	shader->setUniformMat4x4f("_view", 1, glm::value_ptr(camera.getView()));
	shader->setUniformMat4x4f("_model", 1, glm::value_ptr(transform.localToWorld()));

	texture->bind(0);
	shader->setUniform1i("_texture", 0);

	shader->setUniformVec4f("_color", (float)color.r / 255.0f, (float)color.g / 255.0f, (float)color.b / 255.0f, (float)color.a / 255.0f);
	shader->setUniform1f("_textureTransparency", textureTransparency);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);

	texture->unbind();
}

void Square::setCallback(const EventFunc& func)
{
	callbacks.push_back(func);
}

void Square::mouseEvent(MouseButtonEvent* e)
{
	if (e->type == MousePress)
		onMousePress(e);
	else if (e->type == MouseRelease)
		onMouseRelease(e);
}


void Square::onMouseRelease(MouseButtonEvent* e)
{
	std::cout << "mouse release" << std::endl;
}

void Square::onMousePress(MouseButtonEvent* e)
{
	if (eventSate()) {
		for (int i = 0; i < callbacks.size(); i++) {
			callbacks[i]("");
		}
	}
}
