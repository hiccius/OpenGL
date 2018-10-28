#pragma once

#include <string>
#include <GLFW/glfw3.h>

#include "projectionmatrix.h"


class CWindow
{
public:
    CWindow() noexcept;
    ~CWindow() noexcept;

    bool SetUp(int32_t width, int32_t height, const std::string& title) noexcept;
    bool SetProjectionMatrix(EProjection projectionType, float fieldOfView) noexcept;
    void SetResizeCallback(GLFWframebuffersizefun callback) noexcept;

    bool IsOpen() const noexcept;

    void PollCloseKey(int32_t key) const noexcept;
    void RedrawAndPoll() const noexcept;

    glm::f32* GetProjectionMatrixValuePtr() noexcept;

private:
    bool PollKey(int32_t key) const noexcept;
    void UpdateProjectionMatrix(int newWidth, int newHeight) noexcept;

    GLFWwindow* _window;
    int32_t     _initWidth;
    int32_t     _initHeight;
    glm::mat4   _defaultProjection;

    std::unique_ptr<IProjectionMatrix> _projectionMatrix;
};
