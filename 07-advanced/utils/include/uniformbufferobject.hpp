#ifndef UNIFORMBUFFEROBJECT_HPP
#define UNIFORMBUFFEROBJECT_HPP

#include <cstddef>

class CUniformBufferObject
{
public:
    CUniformBufferObject() noexcept;
    ~CUniformBufferObject() noexcept;

    CUniformBufferObject(CUniformBufferObject&& aOther) noexcept;
    CUniformBufferObject(const CUniformBufferObject& aOther) = delete;

    void Allocate(std::size_t aSize) noexcept;
    void SetBindingPoint(unsigned int aBindingPoint) noexcept;

    template<typename ...T>
    void SetData(const T& ...aData) noexcept;

private:
    unsigned int _id;
};

#endif // UNIFORMBUFFEROBJECT_HPP
