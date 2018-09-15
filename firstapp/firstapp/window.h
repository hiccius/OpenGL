#pragma once

#include <string>
#include <GLFW/glfw3.h>

class CWindow
{
public:
    CWindow();
    ~CWindow();

    bool SetUp(int32_t width, int32_t height, const std::string& title);
    void SetResizeCallback(GLFWframebuffersizefun callback);

    bool IsOpen();

    void PollCloseKey(int32_t key);
    void RedrawAndPoll();

private:
    GLFWwindow* _window;
};