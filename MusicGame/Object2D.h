#pragma once

#include "depend.h"
#include "Transform.h"
#include "Camera.h"
#include <vector>

class Object2D
{
public:
	Object2D(Object2D* parent = nullptr, const std::string& type = "Object2D");
	~Object2D();

	virtual void renderSelect(Camera& camera, int code) const = 0;
	virtual void draw(Camera& camera) const = 0;
	
	inline std::string getType() const
	{
		return type;
	}

	inline float width() const
	{
		return _width;
	}
	inline float height() const
	{
		return _height;
	}
	inline void enableEvent()
	{
		respondEvent = true;
	}
	inline void disableEvent() 
	{
		respondEvent = false;
	}
	inline bool eventSate() const
	{
		return respondEvent;
	}

private:
	float _width;
	float _height;

	std::string type;
	bool respondEvent;

	Object2D* parent;
	std::vector<Object2D*> children;
public:
	Transform transform;
	bool active;
};