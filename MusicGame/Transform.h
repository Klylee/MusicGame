#pragma once

#include "depend.h"
#include <glm/gtc/quaternion.hpp>

typedef glm::vec3 Vector3;
typedef glm::qua<float> Quaternion;

class Transform
{
	Vector3 _position;
	Vector3 _eulerAngles;
	Vector3 _scale;
	Quaternion _rotation;
	glm::mat4 _localToWorld;

	void calcuLToW();
public:
	Vector3 position() const;
	void position(Vector3 pos);
	Vector3 eulerAngles() const;
	void eulerAngles(Vector3 eulerangle);
	Vector3 scale() const;
	void scale(Vector3 scale);
	glm::mat4 localToWorld() const;

	Transform();
};



inline void Transform::calcuLToW()
{
	_localToWorld = glm::mat4(1);
	_localToWorld = glm::scale(_localToWorld, _scale);
	_localToWorld = glm::mat4_cast(_rotation) * _localToWorld;
	_localToWorld = glm::translate(_localToWorld, _position);
}