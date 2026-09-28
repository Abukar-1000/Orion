#ifndef SavePointCommand_H
#define SavePointCommand_H
#include <filesystem>
#include "../CommandBase.h"

namespace fs = std::filesystem;
class SavePointCommand : public CommandBase
{
    public:
        SavePointCommand();
        virtual void Execute(const std::string& request) override;
        virtual void Undo(const std::string& request) override;
        virtual bool IsValidRequest(const std::string& request) override;
};

#endif // SavePointCommand_H