#ifndef ICommand_H
#define ICommand_H

class ICommand
{
    public:
        virtual ~ICommand() = default;
        virtual void Execute(const std::string& request) = 0;
        virtual void Undo(const std::string& request) = 0;
        virtual bool IsValidRequest(const std::string& request) = 0;
};

#endif // ICommand_H