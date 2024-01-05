#pragma once

#include "Square.h"
#include <functional>
#include "MouseEvent.h"
#include "AssetsManager.h"


namespace UI {
	typedef std::function<void(std::string)> EventFunc;

	class Button : public Square
	{
		friend class Scene;


		std::vector<EventFunc> callbacks;
		Shader* colorCodeShader;

	protected:
		void renderColorCodeMap(const Camera& camera, int code) const override;
		void mouseEvent(MouseButtonEvent* e);
	public:
		Button(Object2D* parent);
		~Button();

		void setCallback(const EventFunc& func);
		void onMouseRelease(MouseButtonEvent* e);
		void onMousePress(MouseButtonEvent* e);

		void update() override {}
	};

}
