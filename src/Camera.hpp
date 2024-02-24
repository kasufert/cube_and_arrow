#pragma once
#include "header.hpp"

class Camera
{
    glm::vec3 _pos;
    glm::vec3 _viewDir;
    glm::vec2 _sensitivity;
    glm::vec3 _right;
    float _pitch;
    float _yaw;
    static constexpr glm::vec3 UP = { 0.0f, 1.0f, 0.0f };
public:
    Camera();
    inline float pitch_rad()const { return _pitch; };
    inline float yaw_rad()const { return _yaw; };
    glm::mat4 getWorldToViewMat() const;
    glm::vec3 pos() const;
    glm::vec3 viewDir() const;
    void mouseUpdate(const glm::vec2& newMousePos, const glm::vec2& center);
    void reposition(const glm::vec3& newPos, const glm::vec3 viewDir);
    void moveForward(float mag);
    void moveRight(float mag);
    void moveUp(float mag);
};