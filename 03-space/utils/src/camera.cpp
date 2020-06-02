#include "camera.hpp"

#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include "matrixderived.hpp"

void CCamera::SetYaw(double aXOffset) noexcept
{
    _yaw += _sensitivity * aXOffset;
}

void CCamera::SetPitch(double aYOffset) noexcept
{
    _pitch = std::clamp(_pitch + _sensitivity * aYOffset, -89.0, 89.0);
}

void CCamera::SetFoV(double aYOffset) noexcept
{
    _fov = std::clamp(_fov - aYOffset, 1.0, 45.0);
    _perspectiveMatrix.reset();
}

void CCamera::Move(Direction aDirection, double aSpeed) noexcept
{
    auto velocity{static_cast<float>(aSpeed * _movementSpeedFactor)};

    switch (aDirection)
    {
    case Direction::Forward:
        _position += velocity * _direction;
        break;
    case Direction::Back:
        _position -= velocity * _direction;
        break;
    case Direction::Left:
        _position -= velocity * _rightNormal;
        break;
    case Direction::Right:
        _position += velocity * _rightNormal;
        break;
    }

    _viewMatrix.reset();
}

void CCamera::RecalculateDirection() noexcept
{
    _direction.x = std::cos(glm::radians(_pitch)) * std::cos(glm::radians(_yaw));
    _direction.y = std::sin(glm::radians(_pitch));
    _direction.z = std::cos(glm::radians(_pitch)) * std::sin(glm::radians(_yaw));

    _rightNormal = glm::normalize(glm::cross(_direction, _upNormal));
    _viewMatrix.reset();
}

const CViewMatrix& CCamera::GetViewMatrix() noexcept
{
    if (!_viewMatrix)
    {
        _viewMatrix = std::make_unique<CViewMatrix>(_position, _position + _direction, _upNormal);
    }

    return *_viewMatrix;
}

const CPerspectiveMatrix& CCamera::GetPerspectiveMatrix() noexcept
{
    if (!_perspectiveMatrix)
    {
        _perspectiveMatrix = std::make_unique<CPerspectiveMatrix>(_fov, _aspectRatio, 0.1f, 100.0f, true);
    }

    return *_perspectiveMatrix;
}
