#pragma once

#include <utility>

#include <glm/glm.hpp>

class CCamera
{
public:
    enum class EMoveDirection
    {
        Forward, Backward, Left, Right
    };

    CCamera() :
        _position{ glm::vec3(0.0f, 0.0f, 3.0f) },
        _front{ glm::vec3(0.0f, 0.0f, -1.0f) },
        _up{ glm::vec3(0.0f, 1.0f, 0.0f) },
        _yaw{ -90.0 }, _pitch{ 0.0 }, _pitchLimits{-89.0, 89.0},
        _movementSensitivity{ 0.75f }, _lookDirectionSensitivity{ 0.05f }
    {}

    void ChangeLookDirection(double deltaPitch, double deltaYaw) noexcept;
    void Move(EMoveDirection moveDirection, float speed) noexcept;
    glm::f32* GetViewMatrixValuePtr() noexcept;

private:
    /// TODO: normalize vectors?
    glm::vec3 _position;
    glm::vec3 _front;
    glm::vec3 _up;

    double _yaw;
    double _pitch;

    std::pair<double, double> _pitchLimits;

    float _movementSensitivity;
    float _lookDirectionSensitivity;

    glm::mat4   _viewMatrix;
};