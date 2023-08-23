#include "Object2D.h"

Object2D::Object2D(Object2D* parent, const std::string& type)
	: transform(), active(true), _width(1), _height(1), parent(parent), type(type), respondEvent(false)
{
	if (parent) {
		parent->children.push_back(this);
	}
}

Object2D::~Object2D()
{
	// destroy all children
}

