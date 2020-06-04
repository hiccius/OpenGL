#include "vertexbufferobject.hpp"

#include <glad/glad.h>

CVertexBufferObject::CVertexBufferObject() noexcept
{
    glGenBuffers(1, &_id);
}

CVertexBufferObject::~CVertexBufferObject() noexcept
{
    glDeleteBuffers(1, &_id);
}
