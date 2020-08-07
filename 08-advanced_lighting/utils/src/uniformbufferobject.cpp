#include "uniformbufferobject.hpp"

#include <glad/glad.h>

CUniformBufferObject::CUniformBufferObject() noexcept
{
    glGenBuffers(1, &_id);
}

CUniformBufferObject::~CUniformBufferObject() noexcept
{
    if (_id != 0)
    {
        glDeleteBuffers(1, &_id);
    }
}

CUniformBufferObject::CUniformBufferObject(CUniformBufferObject&& aOther) noexcept
{
    _id = aOther._id;
    aOther._id = 0;
}

void CUniformBufferObject::Allocate(std::size_t aSize) noexcept
{
    glBindBuffer(GL_UNIFORM_BUFFER, _id);
    glBufferData(GL_UNIFORM_BUFFER, aSize, nullptr, GL_STATIC_DRAW);
}

void CUniformBufferObject::SetBindingPoint(unsigned int aBindingPoint) noexcept
{
    glBindBufferBase(GL_UNIFORM_BUFFER, aBindingPoint , _id);
}
