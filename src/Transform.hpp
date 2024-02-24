#pragma once
#include "header.hpp"

struct Rotation
{
    glm::vec3 _axis = { 0.f, 1.f, 0.f };
    float _angle_rad = 0.f;
};

class Transform
{
    glm::vec3 _position = { 0.f, 0.f, 0.f };
    Rotation _rotation;
    glm::vec3 _scale = { 1.f, 1.f, 1.f };
public:
    Transform();
    void setPosition(glm::vec3 pos);
    void moveBy(glm::vec3 movement);
    void setRotation(Rotation rot);
    void rotateBy(Rotation rot);
    void setScale(glm::vec3 scale);
    void scaleBy(glm::vec3 scale);

    glm::mat4 matrix() const;

    glm::vec3 position() const;
    Rotation rotation() const;
    glm::vec3 scale() const;
};