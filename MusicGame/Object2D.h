#pragma once 

#include "depend.h"
#include "Transform.h"
#include "Camera.h"
#include <vector>
#include <functional>


class Object2D
{
	typedef std::function<void(Object2D*, float)> DestroyFunc;
public:
	Object2D(Object2D* parent = nullptr);
	Object2D(const Object2D &other);
	~Object2D();



	virtual void renderColorCodeMap(const Camera& camera, int code) const {}
	virtual void draw(const Camera& camera) const {}
	virtual void update() {}

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

	void setDestroyDelegate(const DestroyFunc& func)
	{
		destroy = func;
	}
protected:
	float _width;
	float _height;

	bool respondEvent;
	std::string type;

	Object2D* root;
	Object2D* parent;
	std::vector<Object2D*> children;

	DestroyFunc destroy;
public:
	Transform transform;
	bool active;
};
