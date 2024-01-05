#pragma once

#include "Square.h"
#include "Time.h"
#include <functional>

typedef std::function<void()> EventFunc;

class Note : public Square
{
public:
	float speed;

	Note(Object2D* parent) :
		Square(parent), speed(2.0f)
	{

	}
	Note(const Note& note) : Square(note), speed(note.speed) {}

	void update() override
	{
		if (transform.position().y <= 4.0f) {
			active = true;
		}
		transform.position(transform.position() + Vector3(0, -speed * Core::getFrameIntervalTime(), 0));
	}

	Note* duplicate()
	{
		Note* newobj = new Note(*this);
		return newobj;
	}
};

