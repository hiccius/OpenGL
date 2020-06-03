#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <memory>
#include "matrixderived.hpp"

class CCamera
{
public:
    enum class Direction
    {
        Forward, Back, Left, Right
    };

    constexpr CCamera(double aSensitivity, double aMovementSpeedFactor, double aAspectRatio, bool aFPS = false) noexcept
        : _sensitivity{aSensitivity}, _movementSpeedFactor{aMovementSpeedFactor},
          _aspectRatio{aAspectRatio}, _fpsStyle{aFPS},
          _yaw{-90.0}, _pitch{0.0}, _fov{45.0},
          _upNormal{0.0f, 1.0f, 0.0f}, _rightNormal{1.0f, 0.0f, 0.0f},
          _direction{0.0f, 0.0f, -1.0f}, _position{0.0f, 0.0f, 3.0f}
    {}

    void SetYaw(double aXOffset) noexcept;
    void SetPitch(double aYOffset) noexcept;
    void SetFoV(double aYOffset) noexcept;
    void Move(Direction aDirection, double aSpeed) noexcept;

    void RecalculateDirection() noexcept;

    const CViewMatrix&          GetViewMatrix() noexcept;
    const CPerspectiveMatrix&   GetPerspectiveMatrix() noexcept;

private:
    const double _sensitivity;
    const double _movementSpeedFactor;
    const double _aspectRatio;
    const bool   _fpsStyle;

    double _yaw;
    double _pitch;
    double _fov;

    const glm::vec3 _upNormal;

    glm::vec3   _rightNormal;
    glm::vec3   _direction;
    glm::vec3   _position;

    std::unique_ptr<CViewMatrix>        _viewMatrix;
    std::unique_ptr<CPerspectiveMatrix> _perspectiveMatrix;
};

#endif // CAMERA_HPP
