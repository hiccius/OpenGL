#pragma once

#include <string>
#include <GLFW/glfw3.h>

#include "projection.h"
#include "camera.h"


class CWindow
{
public:
    CWindow() noexcept;
    ~CWindow() noexcept;

    bool SetUp(int32_t width, int32_t height, const std::string& title) noexcept;
    bool SetProjection(EProjection projectionType, float fieldOfView) noexcept;
    void SetResizeCallback() noexcept;

    void SetInputMode(int mode, int value);
    void SetMousePositionCallback() noexcept;
    void SetMouseScrollCallback() noexcept;

    bool IsOpen() const noexcept;

    bool PollKey(int32_t key) const noexcept;
    void PollCloseKey(int32_t key) const noexcept;

    void PollMovementKey(CCamera::EMoveDirection moveDirection, int32_t key) noexcept;

    void RedrawAndPoll() noexcept;

    glm::f32* GetProjectionMatrixValuePtr() noexcept;
    glm::f32* GetViewMatrixValuePtr() noexcept;

private:
    static void UpdateProjection(int newWidth, int newHeight) noexcept;

    GLFWwindow* _window;
    int32_t     _initWidth;
    int32_t     _initHeight;
    glm::mat4   _defaultProjection;

    static CCamera _camera;

    static bool    _firstMouse;
    static double  _mouseXPosition;
    static double  _mouseYPosition;

    float   _deltaFrameTime;
    float   _lastFrameTime;

    static std::unique_ptr<IProjection> _projection;

    static void MousePositionCallback(GLFWwindow* window, double xPosition, double yPosition);
    static void ResizeCallback(GLFWwindow* window, int width, int height);
    static void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
};
