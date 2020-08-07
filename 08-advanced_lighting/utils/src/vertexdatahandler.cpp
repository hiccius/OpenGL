#include "vertexdatahandler.hpp"

#include <glad/glad.h>
#include "helpers.hpp"
#include "vertexbufferobject.hpp"

CVertexDataHandler::CVertexDataHandler() noexcept
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
    : _vbo{std::move(aOther._vbo)}, _vaoId{aOther._vaoId}, _eboId{aOther._eboId},
      _lastAttributeIndex{aOther._lastAttributeIndex}
{
    aOther._vbo.clear();
    aOther._vaoId = 0;
    aOther._eboId = 0;
    aOther._lastAttributeIndex = 0;
}

void CVertexDataHandler::AddVertexBufferObject(CVertexBufferObject* aVBO)
{
    if(!aVBO)
    {
        throw OpenGLException("VERTEX", "Invalid pointer to VBO");
    }

    _vbo.push_back(aVBO);
}

void CVertexDataHandler::AddAttribute(unsigned int aComponents, unsigned int aStride, unsigned int aOffset, bool aBytes) noexcept
{
    glVertexAttribPointer(_lastAttributeIndex, aComponents, GL_FLOAT, GL_FALSE,
                          aStride * (aBytes ? 1 : sizeof(float)),
                          reinterpret_cast<void*>(aOffset * (aBytes ? 1 : sizeof(float))));
    glEnableVertexAttribArray(_lastAttributeIndex);
    ++_lastAttributeIndex;
}

void CVertexDataHandler::AddAttributeDivisor(unsigned int aComponents, unsigned int aStride, unsigned int aOffset, unsigned int aDivisor, bool aBytes) noexcept
{
    glVertexAttribPointer(_lastAttributeIndex, aComponents, GL_FLOAT, GL_FALSE,
                          aStride * (aBytes ? 1 : sizeof(float)),
                          reinterpret_cast<void*>(aOffset * (aBytes ? 1 : sizeof(float))));
    glEnableVertexAttribArray(_lastAttributeIndex);
    glVertexAttribDivisor(_lastAttributeIndex, aDivisor);
    ++_lastAttributeIndex;
}

void CVertexDataHandler::DrawArrays(int aNumberVertices) const noexcept
{
    glBindVertexArray(_vaoId);
    glDrawArrays(GL_TRIANGLES, 0, aNumberVertices);
}

void CVertexDataHandler::DrawArrays(int aNumberVertices, int aInstances) const noexcept
{
    glBindVertexArray(_vaoId);
    glDrawArraysInstanced(GL_TRIANGLES, 0, aNumberVertices, aInstances);
}

void CVertexDataHandler::DrawElements(int aNumberVertices) const noexcept
{
    glBindVertexArray(_vaoId);
    glDrawElements(GL_TRIANGLES, aNumberVertices, GL_UNSIGNED_INT, 0);
}

void CVertexDataHandler::DrawElements(int aNumberVertices, int aInstances) const noexcept
{
    glBindVertexArray(_vaoId);
    glDrawElementsInstanced(GL_TRIANGLES, aNumberVertices, GL_UNSIGNED_INT, 0, aInstances);
}

void CVertexDataHandler::DrawPoints(int aNumberPoints) const noexcept
{
    glBindVertexArray(_vaoId);
    glDrawArrays(GL_POINTS, 0, aNumberPoints);
}

void CVertexDataHandler::BindVAO() const noexcept
{
    glBindVertexArray(_vaoId);
}
