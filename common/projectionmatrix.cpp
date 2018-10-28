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
    float newAspectRatio = static_cast<float>(newWidth) / static_cast<float>(newHeight);

    float newFovRadians;
    if (newAspectRatio >= initAspectRatio)
        newFovRadians = glm::radians(_initFovDegrees);
    else
        newFovRadians = CalculateProportionalFovRadians(initAspectRatio / newAspectRatio);

    _matrix = glm::perspective(newFovRadians, newAspectRatio, 0.1f, 100.0f);
}


void CPerspectiveConstant::Calculate(int newWidth, int newHeight) noexcept
{
    float newAspectRatio = static_cast<float>(newWidth) / static_cast<float>(newHeight);
    float newFovRadians = CalculateProportionalFovRadians(newHeight / _initHeight);

    _matrix = glm::perspective(newFovRadians, newAspectRatio, 0.1f, 100.0f);
}
