#pragma once

#include <string>


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


class OpenGLException : public std::exception
{
public:
    OpenGLException(const std::string& errorString) : _errorString{ errorString } {};

    virtual const char* what() const noexcept override final
    {
        return _errorString.c_str();
    }

private:
    std::string _errorString;
};


template <typename T>
T limitValue(T value, T min, T max)
{
    if (value > max)
    {
        return max;
    }
    else if (value < min)
    {
        return min;
    }
    else
    {
        return value;
    }
}


template <typename T>
T limitValue(T value, std::pair<T, T> limits)
{
    return limitValue(value, limits.first, limits.second);
}


/* Inspired by https://stackoverflow.com/a/48368508 */
template <typename T>
struct lambda_traits : lambda_traits<decltype(&T::operator())>
{ };

template <typename T, typename R, typename... Args>
struct lambda_traits<R(T::*)(Args...) const>
{
    using pointer = R (*)(Args...);

    static pointer lambdaToPointer(T&& t)
    {
        static T fn = std::forward<T>(t);
        return [](Args... args)
        {
            return fn(args...);
        };
    }
};

template <typename T>
typename lambda_traits<T>::pointer lambdaToPointer(T&& t)
{
    return lambda_traits<T>::lambdaToPointer(std::forward<T>(t));
}
