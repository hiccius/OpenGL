#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <array>
#include <vector>

class CVertexDataHandler
{
public:
    CVertexDataHandler() noexcept;
    ~CVertexDataHandler() noexcept;

    template <typename T, std::size_t N>
    void AddBufferObject(const std::array<T, N>& data, GLenum targetBufferObject) noexcept
    {
        GLuint bufferObjectId;
        glGenBuffers(1, &bufferObjectId);

        glBindBuffer(targetBufferObject, bufferObjectId);
        glBufferData(targetBufferObject, N * sizeof(T), data.data(), GL_STATIC_DRAW);

        _bufferIds.push_back(bufferObjectId);
    }

    void AddAttributes() const noexcept;

    void DrawArrays() const noexcept;
    void DrawElements() const noexcept;

private:
    GLuint              _vertexArrayObjectId;
    std::vector<GLuint> _bufferIds;
};