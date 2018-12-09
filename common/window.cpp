#include "window.h"

#include <functional>

#include "helpers.h"


bool    CWindow::_firstMouse{ true };
double  CWindow::_mouseXPosition{ 0.0 };
double  CWindow::_mouseYPosition{ 0.0 };
std::unique_ptr<IProjection> CWindow::_projection{ nullptr };
CCamera CWindow::_camera;

CWindow::CWindow() noexcept :
    _window{ nullptr }, _initWidth{ 0 }, _initHeight{ 0 },
    _defaultProjection{ 1.0f }
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for Mac OS X
}


CWindow::~CWindow() noexcept
{
    glfwTerminate();
}


bool CWindow::SetUp(int32_t width, int32_t height, const std::string& title) noexcept
{
    _window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!_window)
    {
        return false;
    }
    else
    {
        _initWidth = width;
        _initHeight = height;

        _mouseXPosition = _initWidth / 2;
        _mouseYPosition = _initHeight / 2;

        glfwMakeContextCurrent(_window);
        glfwSetWindowPos(_window, 100, 100);

        return true;
    }
}


/// TODO: this needs to be called to see something
/// Consider include it in constructor or add a default
bool CWindow::SetProjection(EProjection projectionType, float fieldOfView) noexcept
{
    try
    {
        _projection = IProjection::Create(projectionType, _initWidth, _initHeight, fieldOfView);
        return true;
    }
    catch (const OpenGLException&)
    {
        return false;
    }
}


void CWindow::SetResizeCallback() noexcept
{
    glfwSetFramebufferSizeCallback(_window, &ResizeCallback);
}


void CWindow::ResizeCallback(GLFWwindow* window, int width, int height)
{
    UpdateProjection(width, height);
    glViewport(0, 0, width, height);
}


void CWindow::SetInputMode(int mode, int value)
{
    glfwSetInputMode(_window, mode, value);
}


void CWindow::SetMousePositionCallback() noexcept
{
    glfwSetCursorPosCallback(_window, &MousePositionCallback);
}


void CWindow::MousePositionCallback(GLFWwindow* window, double xPosition, double yPosition)
{
    if (_firstMouse)
    {
        _mouseXPosition = xPosition;
        _mouseYPosition = yPosition;
        _firstMouse = false;
    }

    double xOffset = xPosition - _mouseXPosition;
    double yOffset = yPosition - _mouseYPosition;

    _mouseXPosition = xPosition;
    _mouseYPosition = yPosition;

    _camera.ChangeLookDirection(-yOffset, xOffset);
}


void CWindow::SetMouseScrollCallback() noexcept
{
    glfwSetScrollCallback(_window, &MouseScrollCallback);
}


void CWindow::MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    _projection->ModifyInitFovDegrees(static_cast<float>(-yOffset));
}


bool CWindow::IsOpen() const noexcept
{
    return !glfwWindowShouldClose(_window);
}


bool CWindow::PollKey(int32_t key) const noexcept
{
    return glfwGetKey(_window, key) == GLFW_PRESS;
}


void CWindow::PollCloseKey(int32_t key) const noexcept
{
    if (PollKey(key))
    {
        glfwSetWindowShouldClose(_window, true);
    }
}


void CWindow::PollMovementKey(CCamera::EMoveDirection moveDirection, int32_t key) noexcept
{
    if (PollKey(key))
    {
        _camera.Move(moveDirection, _deltaFrameTime);
    }
}


void CWindow::RedrawAndPoll() noexcept
{
    glfwSwapBuffers(_window);
    glfwPollEvents();

    float currentFrameTime = static_cast<float>(glfwGetTime());
    _deltaFrameTime = currentFrameTime - _lastFrameTime;
    _lastFrameTime = currentFrameTime;
}


void CWindow::UpdateProjection(int newWidth, int newHeight) noexcept
{
    if (_projection)
    {
        _projection->Calculate(newWidth, newHeight);
    }
}


glm::f32* CWindow::GetProjectionMatrixValuePtr() noexcept
{
    if (_projection)
    {
        return _projection->GetMatrixValuePtr();
    }
    else
    {
        return glm::value_ptr(_defaultProjection);
    }
}


glm::f32* CWindow::GetViewMatrixValuePtr() noexcept
{
    return _camera.GetViewMatrixValuePtr();
}