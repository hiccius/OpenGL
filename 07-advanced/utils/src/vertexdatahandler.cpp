#include "vertexdatahandler.hpp"

#include <glad/glad.h>
#include "helpers.hpp"
#include "vertexbufferobject.hpp"

CVertexDataHandler::CVertexDataHandler() noexcept
    : _vbo{nullptr}
{
    glGenVertexArrays(1, &_vaoId);
    glBindVertexArray(_vaoId);
}

CVertexDataHandler::~CVertexDataHandler() noexcept
{
    if (_vaoId != 0)
    {
        glDeleteVertexArrays(1, &_vaoId);
    }

    if (_eboId != 0)
    {
        glDeleteBuffers(1, &_eboId);
    }
}

CVertexDataHandler::CVertexDataHandler(CVertexDataHandler&& aOther) noexcept
{
    _vaoId = aOther._vaoId;
    aOther._vaoId = 0;

    if (aOther._eboId != 0)
    {
        _eboId = aOther._eboId;
        aOther._eboId = 0;
    }

    _lastAttributeIndex = aOther._lastAttributeIndex;
    _vbo = aOther._vbo;
}

void CVertexDataHandler::AddVertexBufferObject(CVertexBufferObject* aVBO)
{
    if(!aVBO)
    {
        throw OpenGLException("VERTEX", "Invalid pointer to VBO");
    }

    _vbo = aVBO;
}

void CVertexDataHandler::AddAttribute(unsigned int aComponents, unsigned int aStride, unsigned int aOffset, bool aBytes) noexcept
{
    glVertexAttribPointer(_lastAttributeIndex, aComponents, GL_FLOAT, GL_FALSE,
                          aStride * (aBytes ? 1 : sizeof(float)),
                          reinterpret_cast<void*>(aOffset * (aBytes ? 1 : sizeof(float))));
    glEnableVertexAttribArray(_lastAttributeIndex);
    ++_lastAttributeIndex;
}

void CVertexDataHandler::DrawArrays(int aNumberVertices) const noexcept
{
    glBindVertexArray(_vaoId);
    glDrawArrays(GL_TRIANGLES, 0, aNumberVertices);
}

void CVertexDataHandler::DrawElements(int aNumberVertices) const noexcept
{
    glBindVertexArray(_vaoId);
    glDrawElements(GL_TRIANGLES, aNumberVertices, GL_UNSIGNED_INT, 0);
}
