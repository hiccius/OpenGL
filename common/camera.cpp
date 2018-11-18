#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "helpers.h"


void CCamera::ChangeLookDirection(double deltaPitch, double deltaYaw)
{
    _yaw   += deltaYaw;
    _pitch += deltaPitch;

    _pitch = limitValue(_pitch, _pitchLimits);

    double pitchRadians = glm::radians(_pitch);
    double yawRadians = glm::radians(_yaw);

    glm::vec3 front;
    front.x = static_cast<float>(cos(pitchRadians) * cos(yawRadians));
    front.y = static_cast<float>(sin(pitchRadians));
    front.z = static_cast<float>(cos(pitchRadians) * sin(yawRadians));

    _front = glm::normalize(front);
}


void CCamera::Move(EMoveDirection moveDirection, float speed)
{
    switch (moveDirection)
    {
    case EMoveDirection::Forward:
        _position += _front * speed;
        break;
    case EMoveDirection::Backward:
        _position -= _front * speed;
        break;
    case EMoveDirection::Right:
        _position += glm::normalize(glm::cross(_front, _up)) * speed;
        break;
    case EMoveDirection::Left:
        _position -= glm::normalize(glm::cross(_front, _up)) * speed;
        break;
    }
}


glm::mat4 CCamera::CreateViewMatrix()
{
    return glm::lookAt(_position, _position + _front, _up);
}