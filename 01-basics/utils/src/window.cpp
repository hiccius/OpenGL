#include "window.hpp"

#include "helpers.hpp"


CWindow::CWindow() noexcept
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
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
        throw OpenGLException{"Failed to create GLFW window"};
    }

    glfwMakeContextCurrent(_window);

    // Set window coordinates and adjust when resizing
    SetResizeCallback([](GLFWwindow*, int width, int height)
    {
        glViewport(0, 0, width, height);
    });
}

void CWindow::SetResizeCallback(ResizeCallback aCallback) const noexcept
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

void CWindow::PollCloseKey(int aKey) const noexcept
{
    if (PollKey(aKey))
    {
        glfwSetWindowShouldClose(_window, true);
    }
}

void CWindow::ClearColor(float aX, float aY, float aZ, float aW) const noexcept
{
    glClearColor(aX, aY, aZ, aW);
    glClear(GL_COLOR_BUFFER_BIT);
}

void CWindow::RedrawAndPoll() const noexcept
{
    glfwSwapBuffers(_window);
    glfwPollEvents();
}

double CWindow::GetTime() const noexcept
{
    return glfwGetTime();
}
