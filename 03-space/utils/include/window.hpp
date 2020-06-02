#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>   // needs to be included always before GLFW
#include <GLFW/glfw3.h>
#include <string>

class CCamera;
class CWindow
{
public:
    CWindow() noexcept;
    ~CWindow() noexcept;

    void SetUp(int aWidth, int aHeight, std::string_view aTitle, bool aEnableDepthTest = false, CCamera* aCamera = nullptr);
    void SetMouseControl() const;
    bool IsOpen() const noexcept;
    void PollCloseKey(int aCloseKey) const noexcept;
    void PollMovementKeys(int aForwardKey, int aLeftKey, int aBackKey, int aRightKey) noexcept;
    void ClearColor(float aX, float aY, float aZ, float aW) const noexcept;
    void UpdateDeltaFrames() noexcept;
    void RedrawAndPoll() const noexcept;

    template<typename Callable, typename... T>
    void PollCallbackKey(int aKey, Callable&& aCallback, T&&... args) const noexcept;

    double GetTime() const noexcept;

private:
    bool PollKey(int aKey) const noexcept;

    GLFWwindow* _window;
    CCamera*    _camera;
    bool        _depthTest;
    bool        _firstMouse;
    double      _xCursorLocation;
    double      _yCursorLocation;
    double      _lastFrame;
    double      _deltaFrames;
};

namespace Key
{
    static constexpr int Escape = GLFW_KEY_ESCAPE;
    static constexpr int Up     = GLFW_KEY_UP;
    static constexpr int Down   = GLFW_KEY_DOWN;
    static constexpr int W      = GLFW_KEY_W;
    static constexpr int A      = GLFW_KEY_A;
    static constexpr int S      = GLFW_KEY_S;
    static constexpr int D      = GLFW_KEY_D;
};

#endif // WINDOW_HPP
