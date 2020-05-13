#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GLFW/glfw3.h>
#include <string>


class CWindow
{
public:
    using ResizeCallback = void (*) (GLFWwindow*, int, int);

    CWindow() noexcept;
    ~CWindow() noexcept;

    void SetUp(int aWidth, int aHeight, std::string_view aTitle);
    void SetResizeCallback(ResizeCallback aCallback) noexcept;
    bool IsOpen() const noexcept;
    void PollCloseKey(int aCloseKey) noexcept;
    void RedrawAndPoll() noexcept;

private:
    bool PollKey(int aKey) const noexcept;

    GLFWwindow* _window;
};

#endif // WINDOW_HPP
