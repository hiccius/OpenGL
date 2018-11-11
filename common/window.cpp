#include "window.h"

#include "helpers.h"

CWindow::CWindow() noexcept :
    _window{ nullptr }, _initWidth{ 0 }, _initHeight{ 0 },
    _defaultProjection{ 1.0f }, _projectionMatrix{ nullptr }
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

        glfwMakeContextCurrent(_window);
        glfwSetWindowPos(_window, 100, 100);

        return true;
    }
}


/// TODO: this needs to be called to see something
/// Consider include it in constructor or add a default
bool CWindow::SetProjectionMatrix(EProjection projectionType, float fieldOfView) noexcept
{
    try
    {
        _projectionMatrix = IProjectionMatrix::Create(projectionType, _initWidth, _initHeight, fieldOfView);
        return true;
    }
    catch (const OpenGLException&)
    {
        return false;
    }
}


void CWindow::SetResizeCallback(GLFWframebuffersizefun callback) noexcept
{
    auto wrappedCallback = lambdaToPointer([this, callback](GLFWwindow* window, int newWidth, int newHeight)
    {
        UpdateProjectionMatrix(newWidth, newHeight);
        callback(window, newWidth, newHeight);
    });

    glfwSetFramebufferSizeCallback(_window, wrappedCallback);
}


void CWindow::SetInputMode(int mode, int value)
{
    glfwSetInputMode(_window, mode, value);
}


void CWindow::SetMousePositionCallback(GLFWcursorposfun callback) noexcept
{
    auto wrappedCallback = lambdaToPointer([this, callback](GLFWwindow* window, double xPosition, double yPosition)
    {
        callback(window, xPosition, yPosition);
    });

    glfwSetCursorPosCallback(_window, callback);
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


void CWindow::RedrawAndPoll() const noexcept
{
    glfwSwapBuffers(_window);
    glfwPollEvents();
}


void CWindow::UpdateProjectionMatrix(int newWidth, int newHeight) noexcept
{
    if (_projectionMatrix)
    {
        _projectionMatrix->Calculate(newWidth, newHeight);
    }
}


glm::f32* CWindow::GetProjectionMatrixValuePtr() noexcept
{
    if (_projectionMatrix)
    {
        return _projectionMatrix->GetMatrixValuePtr();
    }
    else
    {
        return glm::value_ptr(_defaultProjection);
    }
}
