#include "vertexbufferobject.hpp"

#include <glad/glad.h>

template<std::size_t N>
void CVertexBufferObject::AddVertexData(const float (&aVertices)[N]) const noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(aVertices), aVertices, GL_STATIC_DRAW);
}

template<typename T, typename>
auto CVertexBufferObject::AddVertexData(const std::vector<T>& aVertices) const noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferData(GL_ARRAY_BUFFER, aVertices.size() * sizeof(T), aVertices.data(), GL_STATIC_DRAW);
}

template<typename T, typename>
void CVertexBufferObject::AddVertexData(const std::vector<T>& aVertices) const noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferData(GL_ARRAY_BUFFER, aVertices.size() * T::Size(), aVertices.data(), GL_STATIC_DRAW);
}
