#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>



namespace Core {
	class Time
	{
		double start;
	public:
		Time() : start(0) {}
		void startTimer() { start = glfwGetTime(); }
		double currentTime() { return glfwGetTime() - start; }
	};

	extern double frameInterval;
	static double getFrameIntervalTime() { return frameInterval; }
}
