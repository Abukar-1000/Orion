#include "../../../include/Command/Commands/SavePointMoveCommand.h"


void SavePointMoveCommand::Execute(const std::string& request)
{
    try
    {
        auto args = this->GetArguments(request, ' ');
        auto command = SavePointCommand();
        auto prevPath = fs::current_path();

        if (args.size() < 2)
        {
            std::string msg = std::format(
                "No save point path provided. Request: '{}'", 
                request
            );
            errlogger.Log(msg);
            throw std::invalid_argument(msg);
        }

        auto folderName = this->GetFolderName(args[1]);
        auto savePointPath = fs::current_path() / folderName;
        command.Execute("sp " + folderName);

        // move
        std::error_code ec; 
        fs::current_path(savePointPath, ec);
        if (ec)
        {
            std::string errorDetails = ec.message();
            std::string msg = std::format(R"(
                    Failed to move to save point path: '{}', 
                    Request: '{}', 
                    Error: '{}'
                )", 
                savePointPath.string(), 
                request, 
                errorDetails
            );
            errlogger.Log(msg);
            throw std::runtime_error(msg);
        }

        std::string logMsg = std::format(
            "{},{},{}", 
            "spm", 
            prevPath.string(), 
            savePointPath.string()
        );
        
        logger.Log(logMsg);
    }
    catch (const std::exception& e)
    {
        errlogger.Log(std::format("Error executing SavePointCommand: {}", e.what()));
        throw;
    }
}

bool SavePointMoveCommand::IsValidRequest(const std::string& request)
{
    auto args = this->GetArguments(request, ' ');
    
    if (args.empty() || args[0] != "spm")
    {
        return false;
    }
    
    return true;
}

void SavePointMoveCommand::Undo(const std::string& request)
{}

SavePointMoveCommand::SavePointMoveCommand()
{}