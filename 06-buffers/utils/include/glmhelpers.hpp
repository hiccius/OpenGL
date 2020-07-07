#ifndef GLMHELPERS_HPP
#define GLMHELPERS_HPP

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


template<typename T, typename U>
decltype(auto) DistanceVector3(const T& aVectorA, const U& aVectorB)
{
    return glm::length(glm::vec3{aVectorA[0], aVectorA[1], aVectorA[2]} -
                       glm::vec3{aVectorB[0], aVectorB[1], aVectorB[2]});
}

template<typename T>
T DistanceVector3(const T* aVectorA, const T* aVectorB)
{
    return glm::length(glm::make_vec3(aVectorA) - glm::make_vec3(aVectorB));
}

#endif // GLMHELPERS_HPP
