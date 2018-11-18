#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class IProjection;
using TProjectionPtr = std::unique_ptr<IProjection>;

enum class EProjection
{
    PerspectiveProportional,
    PerspectiveConstant
};

class IProjection
{
public:
    static TProjectionPtr Create(EProjection aProjection, int aInitWidth, int aInitHeight,
                                 float aInitFovDegrees);

    IProjection(int aInitWidth, int aInitHeight, float aInitFovDegrees) noexcept
        : _initWidth{ static_cast<float>(aInitWidth) }, _initHeight{ static_cast<float>(aInitHeight) },
          _initFovDegrees{ aInitFovDegrees },
          _currentAspectRatio{ static_cast<float>(aInitWidth) / static_cast<float>(aInitHeight) },
          _matrix{ glm::perspective(glm::radians(aInitFovDegrees),
                                    static_cast<float>(aInitWidth) / static_cast<float>(aInitHeight), 0.1f, 100.0f) }
    {}

    virtual ~IProjection() noexcept {}

    void ModifyInitFovDegrees(float aDeltaFovDegrees) noexcept;

    virtual void Calculate(int newWidth, int newHeight) = 0;

    glm::f32* GetMatrixValuePtr() noexcept;

protected:
    virtual void UpdateProjection() = 0;
    float CalculateProportionalFovRadians(float newRatio) const noexcept;

    glm::mat4 _matrix;

    float _initWidth;
    float _initHeight;
    float _initFovDegrees;

    float _currentAspectRatio;
};


class CPerspectiveProportional : public IProjection
{
public:
    CPerspectiveProportional(int aInitWidth, int aInitHeight, float aInitFov) noexcept
        : IProjection{aInitWidth, aInitHeight, aInitFov},
          _initAspectRatio{ static_cast<float>(aInitWidth) / static_cast<float>(aInitHeight) }
    {}

    virtual void Calculate(int newWidth, int newHeight) noexcept override final;

private:
    virtual void UpdateProjection() noexcept override final;

    float _initAspectRatio;
};


class CPerspectiveConstant : public IProjection
{
public:
    CPerspectiveConstant(int aInitWidth, int aInitHeight, float aInitFov) noexcept
        : IProjection{ aInitWidth, aInitHeight, aInitFov },
          _currentHeight{aInitHeight}
    {}

    virtual void Calculate(int newWidth, int newHeight) noexcept override final;

private:
    virtual void UpdateProjection() noexcept override final;

    int _currentHeight;
};
