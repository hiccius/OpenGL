#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <exception>
#include <filesystem>


class OpenGLException : public std::exception
{
public:
    OpenGLException(const std::string& context, const std::string& errorString) noexcept
        : _context{context}, _errorString{errorString}
    {};

    virtual const char* what() const noexcept final
    {
        return std::string{"ERROR" + GetContext() + " - " + GetError()}.c_str();
    }

    std::string GetContext() const noexcept
    {
        return (!_context.empty() ? "::" : "") + _context;
    }

    std::string GetError() const noexcept
    {
        return _errorString;
    }

private:
    std::string _context;
    std::string _errorString;
};


inline std::filesystem::path GetFullPath(const std::filesystem::path& localPath)
{
    try
    {
        auto folder = std::filesystem::current_path() / PROJECT_DIR / localPath.parent_path();
        if (!std::filesystem::exists(folder))
        {
            throw OpenGLException{"FILESYSTEM", "Folder '" + folder.string() + "' doesn't exist"};
        }

        auto filePath = folder / localPath.filename();
        if (!std::filesystem::exists(filePath))
        {
            throw OpenGLException{"FILESYSTEM", "File '" + filePath.string() + "' doesn't exist"};
        }

        return filePath;
    }
    catch (const std::filesystem::filesystem_error& exc)
    {
        throw OpenGLException{"FILESYSTEM", "Exception accesing '" + localPath.string() + "': " + exc.what()};
    }
}

#endif // HELPERS_HPP
