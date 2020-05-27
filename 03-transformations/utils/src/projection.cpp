#include "projection.hpp"

#include <glm/gtc/matrix_transform.hpp>

CPerspective::CPerspective(float aFoV, float aAspect, float aNear, float aFar, bool aDegrees) noexcept
    : CMatrix{glm::perspective(aDegrees ? glm::radians(aFoV) : aFoV, aAspect, aNear, aFar)}
{}
