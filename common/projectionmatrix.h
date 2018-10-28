#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class IProjectionMatrix;
using TProjectionMatrixPtr = std::unique_ptr<IProjectionMatrix>;

enum class EProjection
{
    PerspectiveProportional,
    PerspectiveConstant
};

class IProjectionMatrix
{
public:
    static TProjectionMatrixPtr Create(EProjection aProjection, int aInitWidth, int aInitHeight,
                                       float aInitFovDegrees);

    IProjectionMatrix(int aInitWidth, int aInitHeight, float aInitFovDegrees) noexcept
        : _initWidth{ static_cast<float>(aInitWidth) }, _initHeight{ static_cast<float>(aInitHeight) },
          _initFovDegrees{ aInitFovDegrees },
          _matrix{ glm::perspective(glm::radians(aInitFovDegrees),
                                    static_cast<float>(aInitWidth) / static_cast<float>(aInitHeight), 0.1f, 100.0f) }
    {}

    virtual ~IProjectionMatrix() noexcept {}

    virtual void Calculate(int newWidth, int newHeight) noexcept = 0;

    glm::f32* GetMatrixValuePtr() noexcept;

protected:
    glm::mat4 _matrix;

    float _initWidth;
    float _initHeight;
    float _initFovDegrees;

    float CalculateProportionalFovRadians(float newRatio) const noexcept;
};


class CPerspectiveProportional : public IProjectionMatrix
{
public:
    CPerspectiveProportional(int aInitWidth, int aInitHeight, float aInitFov) noexcept
        : IProjectionMatrix{aInitWidth, aInitHeight, aInitFov},
          initAspectRatio{ static_cast<float>(aInitWidth) / static_cast<float>(aInitHeight) }
    {}

    virtual void Calculate(int newWidth, int newHeight) noexcept override final;

private:
    float initAspectRatio;
};


class CPerspectiveConstant : public IProjectionMatrix
{
public:
    CPerspectiveConstant(int aInitWidth, int aInitHeight, float aInitFov) noexcept
        : IProjectionMatrix{ aInitWidth, aInitHeight, aInitFov }
    {}

    virtual void Calculate(int newWidth, int newHeight) noexcept override final;
};
