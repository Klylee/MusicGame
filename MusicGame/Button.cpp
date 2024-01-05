#include "Button.h"


namespace UI {
	void Button::renderColorCodeMap(const Camera& camera, int code) const
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

	Button::Button(Object2D* parent) : Square(parent)
	{
		type = "UI";
		colorCodeShader = assetsManager.loadShader(std::string(ROOT_PATH) + "assets/Shaders/ColorCode.shader");
	}

	Button::~Button()
	{
	}

	void Button::setCallback(const EventFunc& func)
	{
		callbacks.push_back(func);
	}

	void Button::mouseEvent(MouseButtonEvent* e)
	{
		if (e->type == MousePress)
			onMousePress(e);
		else if (e->type == MouseRelease)
			onMouseRelease(e);
	}


	void Button::onMouseRelease(MouseButtonEvent* e)
	{
		std::cout << "mouse release" << std::endl;
	}

	void Button::onMousePress(MouseButtonEvent* e)
	{
		if (eventSate()) {
			for (int i = 0; i < callbacks.size(); i++) {
				callbacks[i]("");
			}
		}
	}
}
