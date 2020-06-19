#ifndef VERTEXBUFFEROBJECT_HPP
#define VERTEXBUFFEROBJECT_HPP

#include <cstddef>
#include <vector>

class CVertexBufferObject
{
public:
    CVertexBufferObject() noexcept;
    ~CVertexBufferObject() noexcept;

    template<std::size_t N>
    void AddVertexData(const float (&aVertices)[N]) const noexcept;

    template<typename T>
    void AddVertexData(const std::vector<T>& aVertices) const noexcept;

private:
    unsigned int _id;
};

#endif // VERTEXBUFFEROBJECT_HPP
