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

template<std::size_t N>
using StringViewArrray = std::array<std::string_view, N>;

template<std::size_t N>
std::tuple<bool, bool, StringViewArrray<N>> CommandOptionArgs(std::string_view optionKeyword,
                                                              std::string_view optionDescription,
                                                              int argc, char* argv[], std::ostream& out,
                                                              StringViewArrray<N> argKeywords)
{
    if (static_cast<unsigned int>(argc) > N)
    {
        std::string_view firstArg{argv[1]};
        if (firstArg == "--" + std::string{optionKeyword})
        {
            if (static_cast<unsigned int>(argc) > N+1)
            {
                StringViewArrray<N> args;
                for (std::size_t i = 0; i < N; ++i)
                {
                    args[i] = argv[i + 2];
                }
                return std::make_tuple(false, true, std::move(args));
            }
        }
        else if (firstArg != "--help")
        {
            StringViewArrray<N> args;
            for (std::size_t i = 0; i < N; ++i)
            {
                args[i] = argv[i + 1];
            }
            return std::make_tuple(false, false, std::move(args));
        }
    }

    auto tabSize{optionKeyword.size() + 7};
    out.setf(std::ios_base::left, std::ios_base::adjustfield);
    out << "Usage: " << argv[0] << " [option]";
    std::for_each(argKeywords.begin(), argKeywords.end(),
                  [&out](const auto& arg){out << " " << arg;});
    out << "\n\n";
    out << "Options:\n";
    out << std::setw(tabSize) << "  --" + std::string{optionKeyword};
    out << optionDescription << "\n";
    out << std::setw(tabSize) << "  --help";
    out << "Displays this message\n\n";
    return std::make_tuple(true, false, StringViewArrray<N>{});
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
            auto tabSize{optionKeyword.size() + 7};
            out.setf(std::ios_base::left, std::ios_base::adjustfield);
            out << "Usage: " << argv[0] << " [option]\n\n";
            out << "Options:\n";
            out << std::setw(tabSize) << "  --" + std::string{optionKeyword};
            out << optionDescription << "\n";
            out << std::setw(tabSize) << "  --help";
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

template <typename T, typename = void>
struct TSupportsSize : std::false_type{};

template <typename T>
struct TSupportsSize<T, std::void_t<decltype(std::declval<T>().Size())>> : std::true_type{};

#endif // HELPERS_HPP
