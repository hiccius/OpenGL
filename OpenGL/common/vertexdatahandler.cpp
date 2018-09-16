#include "vertexDataHandler.h"


CVertexDataHandler::CVertexDataHandler() noexcept
{
    glGenVertexArrays(1, &_vertexArrayObjectId);
    glBindVertexArray(_vertexArrayObjectId);
}


CVertexDataHandler::~CVertexDataHandler() noexcept
{
    for (const auto& bufferId : _bufferIds)
    {
        glDeleteBuffers(1, &bufferId);
    }
    glDeleteVertexArrays(1, &_vertexArrayObjectId);
}


void CVertexDataHandler::AddAttributes() const noexcept
{
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);
}


void CVertexDataHandler::DrawArrays() const noexcept
{
    glBindVertexArray(_vertexArrayObjectId);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}


void CVertexDataHandler::DrawElements() const noexcept
{
    glBindVertexArray(_vertexArrayObjectId);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}