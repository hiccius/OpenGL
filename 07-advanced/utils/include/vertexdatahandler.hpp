#ifndef VERTEXDATAHANDLER_HPP
#define VERTEXDATAHANDLER_HPP

#include <cstddef>
#include <vector>

class CVertexBufferObject;

class CVertexDataHandler
{
public:
    CVertexDataHandler() noexcept;
    ~CVertexDataHandler() noexcept;

    CVertexDataHandler(CVertexDataHandler&& aOther) noexcept;

    void AddVertexBufferObject(CVertexBufferObject* aVBO);

    template<std::size_t N>
    void AddElementBufferObject(int (&aIndices)[N]) noexcept;
    template<typename T>
    void AddElementBufferObject(const std::vector<T>& aIndices) noexcept;

    void AddAttribute(unsigned int aComponents, unsigned int aStride, unsigned int aOffset, bool aBytes = true) noexcept;

    void DrawArrays(int aNumberOfVertices) const noexcept;
    void DrawElements(int aNumberOfVertices) const noexcept;
    void DrawPoints(int aNumberPoints) const noexcept;


private:
    CVertexBufferObject*    _vbo;
    unsigned int            _vaoId;
    unsigned int            _eboId{0};
    unsigned int            _lastAttributeIndex{0};
};

#endif // VERTEXDATAHANDLER_HPP
