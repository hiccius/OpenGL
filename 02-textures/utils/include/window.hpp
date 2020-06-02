#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>   // needs to be included always before GLFW
#include <GLFW/glfw3.h>
#include <string>


class CWindow
{
public:
    using ResizeCallback = void (*) (GLFWwindow*, int, int);

    CWindow() noexcept;
    ~CWindow() noexcept;

    void SetUp(int aWidth, int aHeight, std::string_view aTitle);
    void SetResizeCallback(ResizeCallback aCallback) const noexcept;
    bool IsOpen() const noexcept;
    void PollCloseKey(int aCloseKey) const noexcept;
    void ClearColor(float aX, float aY, float aZ, float aW) const noexcept;
    void RedrawAndPoll() const noexcept;

    template<typename Callable, typename... T>
    void PollCallbackKey(int aKey, Callable&& aCallback, T&&... args) const noexcept;

    double GetTime() const noexcept;

private:
    bool PollKey(int aKey) const noexcept;

    GLFWwindow* _window;
};

namespace Key
{
    static constexpr int Escape = GLFW_KEY_ESCAPE;
    static constexpr int Up     = GLFW_KEY_UP;
    static constexpr int Down   = GLFW_KEY_DOWN;
};

#endif // WINDOW_HPP
