#ifndef ILogger_H
#define ILogger_H
#include <string>

class ILogger 
{
    public:
        virtual ~ILogger() = default;
        virtual void Clear() = 0;
        virtual bool TryClear() noexcept = 0;
        virtual void Log(const std::string& message) = 0;
};


#endif // ILogger_H