#include "Transform.h"


Vector3 Transform::position() const
{
    return _position;
}

void Transform::position(Vector3 pos)
{
    _position = pos;
    calcuLToW();
}

Vector3 Transform::eulerAngles() const
{
    return _eulerAngles;
}

void Transform::eulerAngles(Vector3 eulerangle)
{
    _eulerAngles = eulerangle;
    _rotation = glm::qua<float>(glm::radians(_eulerAngles));
    calcuLToW();
}

Vector3 Transform::scale() const
{
    return _scale;
}

void Transform::scale(Vector3 scale)
{
    _scale = scale;
    calcuLToW();
}

glm::mat4 Transform::localToWorld() const
{
    return _localToWorld;
}

Transform::Transform()
    : _position(0), _eulerAngles(0), _scale(1)
{
    _rotation = glm::qua<float>(glm::radians(_eulerAngles));
    calcuLToW();
}

