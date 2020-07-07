#include "drawable.hpp"

CDrawableVAO::CDrawableVAO(CVertexDataHandler&& aVertexDataHandler, CVertexBufferObject&& aVertexBufferObject,
                           int aNumVertices, bool aIndexes) noexcept
    : _vertexDataHandler{std::move(aVertexDataHandler)}, _vertexBufferObject{std::move(aVertexBufferObject)},
      _numVertices{aNumVertices}, _indexes{aIndexes}
{
    _vertexDataHandler.AddVertexBufferObject(&_vertexBufferObject);
}

void CDrawableVAO::Draw() const
{
    _indexes ? _vertexDataHandler.DrawElements(_numVertices) : _vertexDataHandler.DrawArrays(_numVertices);
}
