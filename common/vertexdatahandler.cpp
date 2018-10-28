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


void CVertexDataHandler::AddAttributes(GLuint index, GLuint components, GLuint stride, GLuint offset) const noexcept
{
    glVertexAttribPointer(index, components, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat),
                          reinterpret_cast<void *>(offset * sizeof(GLfloat)));
    glEnableVertexAttribArray(index);
}


void CVertexDataHandler::DrawArrays(GLsizei numberOfVertices) const noexcept
{
    glBindVertexArray(_vertexArrayObjectId);
    glDrawArrays(GL_TRIANGLES, 0, numberOfVertices);
}


void CVertexDataHandler::DrawElements() const noexcept
{
    glBindVertexArray(_vertexArrayObjectId);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
