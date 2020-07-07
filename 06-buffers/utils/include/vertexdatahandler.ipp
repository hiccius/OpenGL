#include "vertexdatahandler.hpp"

#include <glad/glad.h>

template<std::size_t N>
void CVertexDataHandler::AddElementBufferObject(int (&aIndices)[N]) noexcept
{
    glGenBuffers(1, &_eboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _eboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(aIndices), aIndices, GL_STATIC_DRAW);
}

template<typename T>
void CVertexDataHandler::AddElementBufferObject(const std::vector<T>& aIndices) noexcept
{
    glGenBuffers(1, &_eboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _eboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, aIndices.size() * sizeof(T), aIndices.data(), GL_STATIC_DRAW);
}
