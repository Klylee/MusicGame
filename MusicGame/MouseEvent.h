#pragma once

#include "depend.h"

enum EventType
{
	MousePress, MouseRelease
};
enum Button
{
	Left, Middle, Right
};

class MouseButtonEvent
{
public:
	glm::vec2 position;
	EventType type;
	Button button;

	explicit MouseButtonEvent(int x, int y, EventType t, Button b);

};