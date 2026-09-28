#include "../../../include/Command/Commands/SavePointCommand.h"


void SavePointCommand::Execute(const std::string& request)
{
    auto args = this->GetArguments(request, ' ');
    std::optional<fs::path> savePointPath = std::nullopt;
    
    bool saveCurrentPath = (
        args.size() < 2 || 
        args[1].empty() ||
        args[1] == "." ||
        args[1] == "./"
    );
    
    if (saveCurrentPath)
    {
        savePointPath = fs::current_path();
    }
    else if (args.size() >= 2 && !args[1].empty())
    {
        bool isFullPath = fs::path(args[1]).is_absolute();
        if (isFullPath)
        {
            savePointPath = fs::path(args[1]);
        }
        else
        {
            savePointPath = fs::current_path() / args[1];
            bool isInvalidPath = !fs::is_directory(*savePointPath);
            
            if (isInvalidPath)
            {
                std::string msg = std::format(
                    "Invalid save point path provided: '{}', Request: '{}', Requested Path: '{}'", 
                    args[1], 
                    request,
                    savePointPath->string()
                );

                errlogger.Log(msg);
                throw std::invalid_argument(msg);
            }

        }
    }
    
    if (!savePointPath.has_value() || savePointPath->empty())
    {
        std::string path = savePointPath.has_value() ? savePointPath->string() : "null";
        std::string msg = std::format(
            "Invalid save point path provided: '{}', Request: '{}'", 
            path, 
            request
        );

        errlogger.Log(msg);
        throw std::invalid_argument(msg);
    }
    
    std::string prevPath = ""; 
    std::string logMsg = std::format(
        "{},{},{}", 
        "sp", 
        prevPath, 
        savePointPath->string()
    );
    
    logger.Log(logMsg);
}

bool SavePointCommand::IsValidRequest(const std::string& request)
{
    auto args = this->GetArguments(request, ' ');
    
    if (args.empty() || args[0] != "sp")
    {
        return false;
    }
    
    return true;
}

void SavePointCommand::Undo(const std::string& request)
{}

SavePointCommand::SavePointCommand()
{}
