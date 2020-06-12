#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <exception>
#include <filesystem>
#include <string_view>
#include <ostream>
#include <cmath>
#include <map>

class OpenGLException : public std::exception
{
public:
    OpenGLException(const std::string& context, const std::string& errorString) noexcept
        : _context{context}, _errorString{errorString}, _fullError{"ERROR" + GetContext() + " - " + GetError()}
    {}

    virtual const char* what() const noexcept final
    {
        return _fullError.c_str();
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
    std::string _fullError;
};

template<typename T>
struct OptionDetails
{
    std::string_view description;
    T                value;
};

template<typename T>
using TCommandOptionMap = std::map<std::string_view, OptionDetails<T>>;

template<typename T>
std::pair<bool, T> CommandOption(TCommandOptionMap<T> aOptions, T aDefault,
                                 int argc, char* argv[], std::ostream& aOut)
{
    if (argc == 2)
    {
        std::string_view option{argv[1]};
        if (option.substr(0, 2) == "--")
        {
            if (auto result = aOptions.find(option.substr(2)); result != aOptions.end())
            {
                return std::make_pair(false, result->second.value);
            }
            else if (option == "--help")
            {
                aOut.setf(std::ios_base::left, std::ios_base::adjustfield);
                aOut << "Usage: " << argv[0] << " [option]\n\n";
                aOut << "Options:\n";
                for (const auto& option : aOptions)
                {
                    aOut << std::setw(15) << "  --" + std::string{option.first};
                    aOut << option.second.description << "\n";
                }
                aOut << std::setw(15) << "  --help";
                aOut << "Displays this message\n\n";
                return std::make_pair(true, aDefault);
            }
        }
    }

    return std::make_pair(false, aDefault);
}

inline std::pair<bool, bool> CommandOption(std::string_view optionKeyword,
                                           std::string_view optionDescription,
                                           int argc, char* argv[], std::ostream& out)
{
    if (argc == 2)
    {
        std::string_view option{argv[1]};
        if (option == "--" + std::string{optionKeyword})
        {
            return std::make_pair(false, true);
        }
        else if (option == "--help")
        {
            out.setf(std::ios_base::left, std::ios_base::adjustfield);
            out << "Usage: " << argv[0] << " [option]\n\n";
            out << "Options:\n";
            out << std::setw(15) << "  --" + std::string{optionKeyword};
            out << optionDescription << "\n";
            out << std::setw(15) << "  --help";
            out << "Displays this message\n\n";
            return std::make_pair(true, false);
        }
    }

    return std::make_pair(false, false);
}

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

template<
    typename T,
    typename = std::enable_if_t<std::is_arithmetic_v<T>>
>
auto GetNumericModifier(T& aValue) noexcept
{
    return [&aValue](const T& aDelta)
           {
               aValue += aDelta;
           };
}

template<
    typename T,
    typename = std::enable_if_t<std::is_arithmetic_v<T>>
>
T ToRadians(const T& aDegrees) noexcept
{
    return aDegrees * M_PI / 180.0;
}

#endif // HELPERS_HPP
