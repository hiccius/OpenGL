#include "projectionmatrix.h"

#include "helpers.h"

TProjectionMatrixPtr IProjectionMatrix::Create(EProjection aProjection, int aInitWidth, int aInitHeight,
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


void IProjectionMatrix::ModifyInitFovDegrees(float aDeltaFovDegrees) noexcept
{
    _initFovDegrees += aDeltaFovDegrees;
    _initFovDegrees = limitValue(_initFovDegrees, 1.0f, 60.0f);

    UpdateProjectionMatrix();
}


glm::f32* IProjectionMatrix::GetMatrixValuePtr() noexcept
{
    return glm::value_ptr(_matrix);
}


float IProjectionMatrix::CalculateProportionalFovRadians(float newRatio) const noexcept
{
    return 2 * atan(newRatio * tan(glm::radians(_initFovDegrees / 2)));
}


void CPerspectiveProportional::Calculate(int newWidth, int newHeight) noexcept
{
    _currentAspectRatio = static_cast<float>(newWidth) / static_cast<float>(newHeight);
    UpdateProjectionMatrix();
}


void CPerspectiveProportional::UpdateProjectionMatrix() noexcept
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

    UpdateProjectionMatrix();
}


void CPerspectiveConstant::UpdateProjectionMatrix() noexcept
{
    float newFovRadians = CalculateProportionalFovRadians(_currentHeight / _initHeight);
    _matrix = glm::perspective(newFovRadians, _currentAspectRatio, 0.1f, 100.0f);
}