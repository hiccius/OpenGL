#include "window.hpp"

#include "helpers.hpp"
#include "camera.hpp"

CWindow::CWindow() noexcept
    : _window{nullptr}, _depthTest{false}, _firstMouse{true}
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

void CWindow::SetUp(int aWidth, int aHeight, std::string_view aTitle, bool aEnableDepthTest, CCamera* aCamera)
{
    _window = glfwCreateWindow(aWidth, aHeight, aTitle.data(), nullptr, nullptr);
    if (!_window)
    {
        throw OpenGLException{"WINDOW", "Failed to create GLFW window"};
    }

    glfwMakeContextCurrent(_window);

    // Set window coordinates and adjust when resizing
    glfwSetFramebufferSizeCallback(_window,
                                   [](GLFWwindow*, int width, int height)
                                   {
                                       glViewport(0, 0, width, height);
                                   });

    // Set window user pointer
    glfwSetWindowUserPointer(_window, this);

    // Load GLAD
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        throw OpenGLException{"GLAD_LOADER", "Failed to initialize GLAD"};
    }

    // Enable depth test if required
    if (aEnableDepthTest)
    {
        _depthTest = true;
        glEnable(GL_DEPTH_TEST);
    }

    // Initialize pointer to camera
    _camera = aCamera;
}

void CWindow::SetMouseControl() const
{
    if (!_camera)
    {
        throw OpenGLException("WINDOW", "Camera not defined before setting mouse control");
    }

    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(_window, [](GLFWwindow* aWindow, double aXLocation, double aYLocation)
                                      {
                                          auto window = static_cast<CWindow*>(glfwGetWindowUserPointer(aWindow));

                                          if (!window->_firstMouse)
                                          {
                                              window->_camera->SetYaw(aXLocation - window->_xCursorLocation);
                                              window->_camera->SetPitch(window->_yCursorLocation - aYLocation);
                                          }
                                          else
                                          {
                                              window->_firstMouse = false;
                                          }

                                          window->_xCursorLocation = aXLocation;
                                          window->_yCursorLocation = aYLocation;

                                          window->_camera->RecalculateDirection();
                                });
    glfwSetScrollCallback(_window, [](GLFWwindow* aWindow, double, double yOffset)
                                   {
                                       auto window = static_cast<CWindow*>(glfwGetWindowUserPointer(aWindow));
                                       window->_camera->SetFoV(yOffset);
                                   });
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

void CWindow::PollMovementKeys(int aForwardKey, int aLeftKey, int aBackKey, int aRightKey) noexcept
{
    if (PollKey(aForwardKey))
    {
        _camera->Move(CCamera::Direction::Forward, _deltaFrames);
    }
    if (PollKey(aLeftKey))
    {
        _camera->Move(CCamera::Direction::Left, _deltaFrames);
    }
    if (PollKey(aBackKey))
    {
        _camera->Move(CCamera::Direction::Back, _deltaFrames);
    }
    if (PollKey(aRightKey))
    {
        _camera->Move(CCamera::Direction::Right, _deltaFrames);
    }
}

void CWindow::ClearColor(float aX, float aY, float aZ, float aW) const noexcept
{
    glClearColor(aX, aY, aZ, aW);

    auto clearMask = GL_COLOR_BUFFER_BIT | (_depthTest ? GL_DEPTH_BUFFER_BIT : 0);
    glClear(clearMask);
}

void CWindow::UpdateDeltaFrames() noexcept
{
    double currentFrame = glfwGetTime();
    _deltaFrames = currentFrame - _lastFrame;
    _lastFrame = currentFrame;
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
