#include "Object2D.h"

Object2D::Object2D(Object2D* parent)
	: root(nullptr), transform(), active(true), _width(1), _height(1), parent(parent), respondEvent(false), type("Object2D")
{
	if (parent) {
		root = parent->root;
		parent->children.push_back(this);
	}
	root = this;
}

Object2D::Object2D(const Object2D& other)
	: root(other.root), transform(other.transform), active(other.active), _width(other._width), _height(other._height), destroy(other.destroy),
	  parent(other.parent), respondEvent(other.respondEvent)
{

}

Object2D::~Object2D()
{
	// destroy all children
}
