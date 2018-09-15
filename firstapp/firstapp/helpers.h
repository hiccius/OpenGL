#pragma once

#include <cstring>


class CStringLiteral
{
public:
    template <std::size_t N>
    constexpr CStringLiteral(const char(&arr)[N]) noexcept :
        _data{ arr }, _size{ N - 1 } {};

    constexpr operator const char* () const noexcept
    {
        return _data;
    };

    constexpr const char* const* operator&() const noexcept
    {
        return &_data;
    };

    constexpr std::size_t size() const noexcept
    {
        return _size;
    };

private:
    const char* const   _data;
    const std::size_t   _size;
};