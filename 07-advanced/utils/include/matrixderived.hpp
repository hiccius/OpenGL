#ifndef MATRIXDERIVED_HPP
#define MATRIXDERIVED_HPP

#include <glm/gtc/matrix_transform.hpp>
#include "matrix.hpp"

class CPerspectiveMatrix : public CMatrix
{
public:
    CPerspectiveMatrix(float aFoV, float aAspect, float aNear, float aFar,
                       bool aDegrees = false) noexcept
        : CMatrix{glm::perspective(aDegrees ? glm::radians(aFoV) : aFoV, aAspect, aNear, aFar)}
    {}
};

class CViewMatrix : public CMatrix
{
public:
    CViewMatrix(const glm::vec3& aPosition, const glm::vec3& aDirection,
                const glm::vec3& aUp = glm::vec3(0.0f, 1.0f, 0.0f)) noexcept
        : CMatrix{glm::lookAt(aPosition, aDirection, aUp)}
    {}
};

class CViewMatrixManual : public CMatrix
{
public:
    CViewMatrixManual(const glm::vec3& aPosition, const glm::vec3& aDirection,
                      const glm::vec3& aUp = glm::vec3(0.0f, 1.0f, 0.0f)) noexcept
    {
        glm::vec3 target = aPosition - aDirection;
        glm::vec3 right  = glm::normalize(glm::cross(aUp, target));
        glm::vec3 up     = glm::normalize(glm::cross(target, right));

        glm::mat4 rotation{1.0f};
        rotation[0][0] = right.x;
        rotation[1][0] = right.y;
        rotation[2][0] = right.z;
        rotation[0][1] = up.x;
        rotation[1][1] = up.y;
        rotation[2][1] = up.z;
        rotation[0][2] = target.x;
        rotation[1][2] = target.y;
        rotation[2][2] = target.z;

        glm::mat4 translation{1.0f};
        translation[3][0] = -aPosition.x;
        translation[3][1] = -aPosition.y;
        translation[3][2] = -aPosition.z;

        glm::mat4 lookAt{rotation * translation};

        _matrix = std::move(lookAt);
    }
};

#endif // MATRIXDERIVED_HPP
