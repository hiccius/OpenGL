#include "vertexdatahandler.hpp"

#include <glad/glad.h>


template<std::size_t N>
void CVertexDataHandler::AddVectorBufferObject(float (&aVertices)[N]) noexcept
{
    glGenBuffers(1, &_vboId);
    glBindBuffer(GL_ARRAY_BUFFER, _vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(aVertices), aVertices, GL_STATIC_DRAW);
}
