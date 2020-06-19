#include "vertexbufferobject.hpp"

#include <glad/glad.h>

CVertexBufferObject::CVertexBufferObject() noexcept
{
    glGenBuffers(1, &_id);
}

CVertexBufferObject::~CVertexBufferObject() noexcept
{
    if (_id != 0)
    {
        glDeleteBuffers(1, &_id);
    }
}

CVertexBufferObject::CVertexBufferObject(CVertexBufferObject&& aOther) noexcept
{
    _id = aOther._id;

    aOther._id = 0;
}
