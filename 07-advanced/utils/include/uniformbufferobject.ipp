#include "uniformbufferobject.hpp"

#include "matrix.hpp"

template<typename ...T>
void SetDataImpl(std::size_t aOffset, const CMatrix& aValue, T ...aData) noexcept
{
    glBufferSubData(GL_UNIFORM_BUFFER, aOffset, aValue.Size(), aValue.GetAddress());
    SetDataImpl(aOffset + aValue.Size(), aData...);
}

void SetDataImpl(std::size_t aOffset, const CMatrix& aValue) noexcept
{
    glBufferSubData(GL_UNIFORM_BUFFER, aOffset, aValue.Size(), aValue.GetAddress());
}

template<typename ...T>
void CUniformBufferObject::SetData(const T& ...aData) noexcept
{
    std::size_t offSet{0};
    glBindBuffer(GL_UNIFORM_BUFFER, _id);
    SetDataImpl(offSet, aData...);
}
