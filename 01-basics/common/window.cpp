#include "window.hpp"

#include <GLFW/glfw3.h>
#include "helpers.hpp"


CWindow::CWindow() noexcept
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

CWindow::~CWindow() noexcept
{
    glfwTerminate();
}

void CWindow::SetUp(int aWidth, int aHeight, std::string_view aTitle)
{
    _window = glfwCreateWindow(aWidth, aHeight, aTitle.data(), nullptr, nullptr);

    if (!_window)
    {
        throw OpenGLException("Failed to create GLFW window");
    }

    /*
    _initWidth = width;
    _initHeight = height;

    _mouseXPosition = _initWidth / 2;
    _mouseYPosition = _initHeight / 2;
    */

    glfwMakeContextCurrent(_window);
    //glfwSetWindowPos(_window, 100, 100);
}

void CWindow::SetResizeCallback(ResizeCallback aCallback) noexcept
{
    glfwSetFramebufferSizeCallback(_window, aCallback);
}

bool CWindow::IsOpen() const noexcept
{
    return !glfwWindowShouldClose(_window);
}

bool CWindow::PollKey(int aKey) const noexcept
{
    return glfwGetKey(_window, aKey) == GLFW_PRESS;
}

void CWindow::PollCloseKey(int aKey) noexcept
{
    if (PollKey(aKey))
    {
        glfwSetWindowShouldClose(_window, true);
    }
}

void CWindow::RedrawAndPoll() noexcept
{
    glfwSwapBuffers(_window);
    glfwPollEvents();
}
