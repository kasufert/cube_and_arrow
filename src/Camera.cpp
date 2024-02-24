#pragma once
#include "Camera.hpp"


Camera::Camera()
    : _viewDir(0.0f, 0.0f, -1.0f), _pos(0.0f, 0.0f, 0.0f), _sensitivity(0.5f, 0.5f), _right(1.0f, 0.0f, 0.0f), _pitch(0.f), _yaw(0.f)
{
}

glm::mat4 Camera::getWorldToViewMat() const
{
    return glm::lookAt(_pos, _pos + _viewDir, UP);
}

glm::vec3 Camera::pos() const
{
    return _pos;
}

glm::vec3 Camera::viewDir() const
{
    return _viewDir;
}

void Camera::mouseUpdate(const glm::vec2& newMousePos, const glm::vec2& center)
{
    glm::vec2 mDelta = newMousePos - center;
    if (glm::length(mDelta) > 50.f)
    {
        return;
    }
    // Yaw
    glm::vec3 newViewDir = glm::normalize(glm::mat3(glm::rotate(glm::radians(-mDelta.x * _sensitivity.x), UP)) * _viewDir);

    // Horiz. Axis
    _right = glm::normalize(glm::cross(_viewDir, UP));

    // Pitch
    newViewDir = glm::normalize(glm::mat3(glm::rotate(glm::radians(-mDelta.y * _sensitivity.y), _right)) * newViewDir);

    float max_pitch = (PI / 2.f) - .1f;
    float max_pitch_complement = (PI / 2.f) - max_pitch;
    if (glm::angle(newViewDir, UP) < max_pitch_complement)
    {
        float compensation = max_pitch_complement - glm::angle(newViewDir, UP);
        newViewDir = glm::normalize(glm::mat3(glm::rotate(-compensation, _right)) * newViewDir);
    }
    if (glm::angle(newViewDir, -UP) < max_pitch_complement)
    {
        float compensation = max_pitch_complement - glm::angle(newViewDir, -UP);
        newViewDir = glm::normalize(glm::mat3(glm::rotate(compensation, _right)) * newViewDir);
    }

    _pitch = (PI / 2.f) - glm::angle(newViewDir, UP);
    _yaw = glm::angle(glm::normalize(glm::vec2{ newViewDir.x, newViewDir.z }), glm::vec2{ 0.0, -1.0f });

    _viewDir = newViewDir;
}

void Camera::reposition(const glm::vec3& newPos, const glm::vec3 newDir)
{
    _viewDir = newDir;
    _pos = newPos;
}

void Camera::moveForward(float mag)
{
    glm::vec3 forward = _viewDir * mag;
    _pos += forward;
}

void Camera::moveRight(float mag)
{
    glm::vec3 rite = _right * mag;
    _pos += rite;
}

void Camera::moveUp(float mag)
{
    _pos += UP * mag;
}
