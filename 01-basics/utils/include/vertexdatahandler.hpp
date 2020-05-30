#ifndef VERTEXDATAHANDLER_HPP
#define VERTEXDATAHANDLER_HPP

#include <cstddef>


class CVertexDataHandler
{
public:
    CVertexDataHandler() noexcept;
    ~CVertexDataHandler() noexcept;

    template<std::size_t N>
    void AddVectorBufferObject(float (&aVertices)[N]) noexcept;
    template<std::size_t N>
    void AddElementBufferObject(int (&aIndices)[N]) noexcept;

    void AddAttribute(unsigned int aComponents, unsigned int aStride, unsigned int aOffset) noexcept;

    void DrawArrays(int aNumberOfVertices) const noexcept;
    void DrawElements(int aNumberOfVertices) const noexcept;

private:
    unsigned int _vboId;
    unsigned int _eboId;
    unsigned int _vaoId;
    unsigned int _lastAttributeIndex{0};
};

#endif // VERTEXDATAHANDLER_HPP
