#ifndef VERTEXDATAHANDLER_HPP
#define VERTEXDATAHANDLER_HPP

#include <cstddef>

class CVertexBufferObject;

class CVertexDataHandler
{
public:
    CVertexDataHandler() noexcept;
    ~CVertexDataHandler() noexcept;

    void AddVertexBufferObject(CVertexBufferObject* aVBO);

    template<std::size_t N>
    void AddElementBufferObject(int (&aIndices)[N]) noexcept;

    void AddAttribute(unsigned int aComponents, unsigned int aStride, unsigned int aOffset) noexcept;

    void DrawArrays(int aNumberOfVertices) const noexcept;
    void DrawElements(int aNumberOfVertices) const noexcept;

private:
    CVertexBufferObject*    _vbo;
    unsigned int            _eboId;
    unsigned int            _vaoId;
    unsigned int            _lastAttributeIndex{0};
};

#endif // VERTEXDATAHANDLER_HPP
