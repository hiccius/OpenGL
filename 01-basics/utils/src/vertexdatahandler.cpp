#include "vertexdatahandler.hpp"

#include <glad/glad.h>


CVertexDataHandler::CVertexDataHandler() noexcept
{
    glGenVertexArrays(1, &_vaoId);
    glBindVertexArray(_vaoId);
}

CVertexDataHandler::~CVertexDataHandler() noexcept
{
    glDeleteVertexArrays(1, &_vaoId);
    glDeleteBuffers(1, &_vboId);
    glDeleteBuffers(1, &_eboId);
}

void CVertexDataHandler::AddAttribute(unsigned int aComponents, unsigned int aStride, unsigned int aOffset) noexcept
{
    glVertexAttribPointer(_lastAttributeIndex, aComponents, GL_FLOAT, GL_FALSE,
                          aStride * sizeof(float), reinterpret_cast<void*>(aOffset * sizeof(float)));
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
