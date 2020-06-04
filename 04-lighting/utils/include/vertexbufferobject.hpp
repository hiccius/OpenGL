#ifndef VERTEXBUFFEROBJECT_HPP
#define VERTEXBUFFEROBJECT_HPP

#include <cstddef>

class CVertexBufferObject
{
public:
    CVertexBufferObject() noexcept;
    ~CVertexBufferObject() noexcept;

    template<std::size_t N>
    void AddVertexData(const float (&aVertices)[N]) const noexcept;

private:
    unsigned int _id;
};

#endif // VERTEXBUFFEROBJECT_HPP
