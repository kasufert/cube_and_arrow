#include "Transform.hpp"



Transform::Transform()
{}

void Transform::setPosition(glm::vec3 pos)
{
    _position = pos;
}

void Transform::moveBy(glm::vec3 movement)
{
    _position += movement;
}

void Transform::setRotation(Rotation rot)
{
}

void Transform::rotateBy(Rotation rot)
{
}

void Transform::setScale(glm::vec3 scale)
{
}

void Transform::scaleBy(glm::vec3 scale)
{
}

glm::mat4 Transform::matrix() const
{
    glm::mat4 trans = glm::translate(_position);
    glm::mat4 rotat = glm::rotate(_rotation._angle_rad, _rotation._axis);
    glm::mat4 scale = glm::scale(_scale);

    return trans * rotat * scale;
}
