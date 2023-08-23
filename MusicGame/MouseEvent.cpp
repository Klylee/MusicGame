#include "MouseEvent.h"

MouseButtonEvent::MouseButtonEvent(int x, int y, EventType t, Button b)
	: position(x, y), type(t), button(b)
{
}
