#ifndef LoggerBase_H
#define LoggerBase_H
#include <chrono>
#include <fstream>
#include <memory>
#include "ILogger.h"
#include <filesystem>
#include "../Config/LogLevels.h"

namespace fs = std::filesystem;
class LoggerBase: public ILogger
{
    private:
        void InitFile();
        static std::string GetTimestamp();
        std::string MapLogLevelToString(uint8_t level);
    protected:
        uint8_t logLevel;
        fs::path logFilePath;
        std::unique_ptr<std::ofstream> stream;
    public:
        LoggerBase();
        LoggerBase(LogLevel level);
        virtual ~LoggerBase();
        virtual void Clear() override;
        virtual bool TryClear() noexcept override;
        virtual void Log(const std::string& message) override;
};

#endif // LoggerBase_H