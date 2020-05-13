#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <exception>


class OpenGLException : public std::exception
{
public:
    OpenGLException(const std::string& errorString) : _errorString{ "ERROR::" + errorString } {};

    virtual const char* what() const noexcept final
    {
        return _errorString.c_str();
    }

private:
    std::string _errorString;
};

#endif // HELPERS_HPP
