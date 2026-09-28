#include "../../include/Command/CommandBase.h"

CommandBase::CommandBase() 
:   logger(LogLevel::Lvl_INFO),
    errlogger(LogLevel::Lvl_ERROR)
{}

std::vector<std::string> CommandBase::GetArguments(const std::string& request, char delimiter)
{
    std::vector<std::string> arguements;
    bool noDelimiters = request.empty() || request.find(delimiter) == std::string::npos;
    if (noDelimiters)
    {
        return arguements;
    }
    
    arguements.reserve(std::count(request.begin(), request.end(), delimiter) + 1);
    
    for (auto &&arg : std::views::split(request, delimiter))
    {
        arguements.emplace_back(arg.begin(), arg.end());
    }

    return arguements;
}

std::string CommandBase::GetFolderName(const std::string& path)
{
    fs::path fsPath(path);
    return fsPath.filename().string();
}