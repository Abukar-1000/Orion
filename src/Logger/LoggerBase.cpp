#include "../../include/Logger/LoggerBase.h"


void LoggerBase::Log(const std::string& message)
{
    bool notInitialized = this->stream == nullptr;
    bool notOpen = this->stream && !this->stream->is_open();
    bool notGood = this->stream && !this->stream->good();

    if (notInitialized || notOpen || notGood)
    {
        std::string errorDetails = notInitialized ? "Stream is not initialized." : 
                                   notOpen ? "Stream is not open." : 
                                   notGood ? "Stream is not good." : 
                                   "Unknown error.";

        std::string logfilePathStr = this->logFilePath.empty() ? 
                                        "unknown" : 
                                        this->logFilePath.string();
        
        std::string errorMsg = std::format(R"(
                {}
                Attempted to log message: {}
                Log file path: {}
            )", 
            errorDetails,
            message, 
            logfilePathStr
        );
        
        throw std::runtime_error(errorMsg);
    }
    
    *(this->stream) << GetTimestamp() 
                    << "," << MapLogLevelToString(logLevel) 
                    << "," << message << "\n";
}

void LoggerBase::Clear()
{
    if (this->stream == nullptr)
    {
        throw std::runtime_error("Log file stream is not initialized.");
    }

    this->stream->close();
    this->stream = std::make_unique<std::ofstream>(this->logFilePath, std::ios::trunc);
    if (!this->stream->is_open()) 
    {
        throw std::runtime_error("Failed to open log file: " + this->logFilePath.string());
    }
    
    std::error_code ec;
    std::filesystem::resize_file(this->logFilePath, 0, ec);
    
    if (ec)
    {
        throw std::runtime_error("Failed to clear log file: " + ec.message());
    }
}

bool LoggerBase::TryClear() noexcept
{
    if (this->stream == nullptr)
    {
        return false;
    }

    std::error_code ec;
    std::filesystem::resize_file(this->logFilePath, 0, ec);
    
    if (ec)
    {
        return false;
    }

    return true;
}

std::string LoggerBase::GetTimestamp()
{
    auto now = std::chrono::system_clock::now();
    auto nowInSeconds = std::chrono::time_point_cast<std::chrono::seconds>(now);
    auto localTime = std::chrono::current_zone()->to_local(nowInSeconds);
    return std::format("{:%Y-%m-%d %H:%M:%S}", localTime);
}

void LoggerBase::InitFile()
{
    std::string filename = this->MapLogLevelToString(logLevel) + ".log";
    this->logFilePath = fs::current_path() / "logs" / filename;
    
    if (!fs::exists(this->logFilePath.parent_path())) 
    {
        fs::create_directories(this->logFilePath.parent_path());
    }

    this->stream = std::make_unique<std::ofstream>(this->logFilePath, std::ios::app);
    if (!this->stream->is_open()) 
    {
        throw std::runtime_error("Failed to open log file: " + this->logFilePath.string());
    }
}

LoggerBase::LoggerBase()
:   logLevel(static_cast<uint8_t>(LogLevel::Lvl_INFO)),
    stream(nullptr)
{
    this->InitFile();
}

LoggerBase::LoggerBase(LogLevel level)
:   logLevel(static_cast<uint8_t>(level)),
    stream(nullptr)
{
    this->InitFile();
}

LoggerBase::~LoggerBase()
{}

std::string LoggerBase::MapLogLevelToString(uint8_t level)
{
    switch (static_cast<LogLevel>(level))
    {
        case LogLevel::Lvl_DEBUG:
            return "DEBUG";
        case LogLevel::Lvl_INFO:
            return "INFO";
        case LogLevel::Lvl_WARNING:
            return "WARNING";
        case LogLevel::Lvl_ERROR:
            return "ERROR";
        case LogLevel::Lvl_FATAL:
            return "FATAL";
        default:
            return "UNKNOWN";
    }
}