#include "window.hpp"


template<typename Callback, typename... T>
void CWindow::PollCallbackKey(int aKey, Callback&& aCallback, T&&... args) const noexcept
{
    if (PollKey(aKey))
    {
        aCallback(std::forward<T>(args)...);
    }
}
