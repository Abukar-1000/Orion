#ifndef SavePointMoveCommand_H
#define SavePointMoveCommand_H
#include "../CommandBase.h"
#include "SavePointCommand.h"

class SavePointMoveCommand : public CommandBase
{
    public:
        SavePointMoveCommand();
        virtual void Execute(const std::string& request) override;
        virtual void Undo(const std::string& request) override;
        virtual bool IsValidRequest(const std::string& request) override;
};

#endif // SavePointMoveCommand_H