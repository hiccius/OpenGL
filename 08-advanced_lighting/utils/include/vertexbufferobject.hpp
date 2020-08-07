#ifndef VERTEXBUFFEROBJECT_HPP
#define VERTEXBUFFEROBJECT_HPP

#include <cstddef>
#include <vector>
#include "helpers.hpp"

class CVertexBufferObject
{
public:
    CVertexBufferObject() noexcept;
    ~CVertexBufferObject() noexcept;

    CVertexBufferObject(CVertexBufferObject&& aOther) noexcept;

    template<std::size_t N>
    void AddVertexData(const float (&aVertices)[N]) const noexcept;

    template<typename T,
             typename = std::enable_if_t<!TSupportsSize<T>::value>>
    auto AddVertexData(const std::vector<T>& aVertices) const noexcept;

    template<typename T,
             typename = std::enable_if_t<TSupportsSize<T>::value>>
    void AddVertexData(const std::vector<T>& aVertices) const noexcept;

private:
    unsigned int _id;
};

#endif // VERTEXBUFFEROBJECT_HPP
