#include "projection.h"

#include "helpers.h"

TProjectionPtr IProjection::Create(EProjection aProjection, int aInitWidth, int aInitHeight,
                                               float aInitFovDegrees)
{
    switch (aProjection)
    {
    case EProjection::PerspectiveConstant:
        return std::make_unique<CPerspectiveConstant>(aInitWidth, aInitHeight, aInitFovDegrees);
    case EProjection::PerspectiveProportional:
        return std::make_unique<CPerspectiveProportional>(aInitWidth, aInitHeight, aInitFovDegrees);
    default:
        throw OpenGLException("Unsopported projection type");
        return nullptr;
    }
}


void IProjection::ModifyInitFovDegrees(float aDeltaFovDegrees) noexcept
{
    _initFovDegrees += aDeltaFovDegrees;
    _initFovDegrees = limitValue(_initFovDegrees, 1.0f, 60.0f);

    UpdateProjection();
}


glm::f32* IProjection::GetMatrixValuePtr() noexcept
{
    return glm::value_ptr(_matrix);
}


float IProjection::CalculateProportionalFovRadians(float newRatio) const noexcept
{
    return 2 * atan(newRatio * tan(glm::radians(_initFovDegrees / 2)));
}


void CPerspectiveProportional::Calculate(int newWidth, int newHeight) noexcept
{
    _currentAspectRatio = static_cast<float>(newWidth) / static_cast<float>(newHeight);
    UpdateProjection();
}


void CPerspectiveProportional::UpdateProjection() noexcept
{
    float newFovRadians;
    if (_currentAspectRatio >= _initAspectRatio)
        newFovRadians = glm::radians(_initFovDegrees);
    else
        newFovRadians = CalculateProportionalFovRadians(_initAspectRatio / _currentAspectRatio);

    _matrix = glm::perspective(newFovRadians, _currentAspectRatio, 0.1f, 100.0f);
}


void CPerspectiveConstant::Calculate(int newWidth, int newHeight) noexcept
{
    _currentAspectRatio = static_cast<float>(newWidth) / static_cast<float>(newHeight);
    _currentHeight = newHeight;

    UpdateProjection();
}


void CPerspectiveConstant::UpdateProjection() noexcept
{
    float newFovRadians = CalculateProportionalFovRadians(_currentHeight / _initHeight);
    _matrix = glm::perspective(newFovRadians, _currentAspectRatio, 0.1f, 100.0f);
}