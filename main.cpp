#include <iostream>
#include <span>
#include <string_view>
#include <filesystem>
#include "./include/Logger/LoggerBase.h"

namespace fs = std::filesystem;
int main(int argc, char** argv){
    std::cout << "Hello, from Orion!\n";
    std::span<char*> args{argv, static_cast<size_t>(argc)};

    for (std::string_view arg : args) 
    {
        std::cout << " - " << arg << '\n';
    }
    
    std::string message = "This is a test log message.";
    LoggerBase logger(LogLevel::Lvl_INFO);
    std::cout << "Logging message: " << message << '\n';
    logger.Log(message);
}
