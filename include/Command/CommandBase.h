#ifndef CommandBase_H
#define CommandBase_H
#include <vector>
#include <string>
#include <ranges>
#include <optional>
#include <algorithm>
#include "ICommand.h"
#include "../Logger/LoggerBase.h"

class CommandBase : public ICommand
{
    protected:
        LoggerBase logger;
        LoggerBase errlogger;
        std::vector<std::string> GetArguments(const std::string& request, char delimiter);
        std::string GetFolderName(const std::string& path);
    public:
        CommandBase();
        virtual ~CommandBase() = default;
        virtual void Execute(const std::string& request) override = 0;
        virtual void Undo(const std::string& request) override = 0;
        virtual bool IsValidRequest(const std::string& request) override = 0;
};

#endif // CommandBase_H