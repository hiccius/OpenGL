#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "vertexdatahandler.hpp"
#include "vertexbufferobject.hpp"

class CDrawable
{
public:
    virtual ~CDrawable() = default;
    virtual void Draw() const = 0;
};

class CDrawableVAO : public CDrawable
{
public:
    CDrawableVAO(CVertexDataHandler&& aVertexDataHandler, CVertexBufferObject&& aVertexBufferObject,
                 int aNumVertices, bool aIndexes = false) noexcept;

    virtual void Draw() const override final;

private:
    CVertexDataHandler  _vertexDataHandler;
    CVertexBufferObject _vertexBufferObject;
    int                 _numVertices;
    bool                _indexes;
};

#endif // DRAWABLE_HPP
