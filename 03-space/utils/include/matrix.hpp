#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <glm/glm.hpp>


class CMatrix
{
public:
    CMatrix() noexcept;

    void Translate(float aX, float aY, float aZ) noexcept;
    void Rotate(float aAngle, float aX, float aY, float aZ, bool aDegrees = false) noexcept;
    void Scale(float aX, float aY, float aZ) noexcept;

    const float* GetAddress() const noexcept;

protected:
    CMatrix(glm::mat4&& aMatrix) noexcept;

private:
    glm::mat4 _matrix;
};

#endif // TRANSFORMATIONMATRIX_HPP