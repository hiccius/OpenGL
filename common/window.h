#pragma once

#include <string>
#include <GLFW/glfw3.h>

class CWindow
{
public:
    CWindow() noexcept;
    ~CWindow() noexcept;

    bool SetUp(int32_t width, int32_t height, const std::string& title) noexcept;
    void SetResizeCallback(GLFWframebuffersizefun callback) const noexcept;

    bool IsOpen() const noexcept;

    bool PollKey(int32_t key) const noexcept;
    void PollCloseKey(int32_t key) const noexcept;
    void RedrawAndPoll() const noexcept;

private:
    GLFWwindow* _window;
};