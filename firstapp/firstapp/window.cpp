#include "window.h"


CWindow::CWindow() noexcept
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
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
        glfwMakeContextCurrent(_window);
        return true;
    }
}


void CWindow::SetResizeCallback(GLFWframebuffersizefun callback) const noexcept
{
    glfwSetFramebufferSizeCallback(_window, callback);
}


bool CWindow::IsOpen() const noexcept
{
    return !glfwWindowShouldClose(_window);
}


void CWindow::PollCloseKey(int32_t key) const noexcept
{
    if (glfwGetKey(_window, key) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(_window, true);
    }
}


void CWindow::RedrawAndPoll() const noexcept
{
    glfwSwapBuffers(_window);
    glfwPollEvents();
}