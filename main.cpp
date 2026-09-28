#include <iostream>
#include <span>
#include <string_view>
#include <filesystem>
#include <string>
#include "./include/Logger/LoggerBase.h"
#include "./include/Command/Commands/SavePointCommand.h"
#include "./include/Command/Commands/SavePointMoveCommand.h"
#include "./include/Keyboard/KeyboardWinStrategy.h"

namespace fs = std::filesystem;
auto to_string(std::string_view sv) -> std::string {
    return std::string(sv);
}

int main(int argc, char** argv){
    std::cout << "Hello, from Orion!\n";
    std::span<char*> args{argv, static_cast<size_t>(argc)};

    int counter = 0;
    std::string argStr =  "";

    for (std::string_view arg : args) 
    {
        std::cout << " - " << to_string(arg) << '\n';
        if (counter > 0)
        {
            argStr += to_string(arg) + " ";
        }
        counter++;
    }

    auto command = SavePointMoveCommand();
    std::cout << "Executing command: '" << "sp " + argStr << "'\n";
    command.Execute("spm " + argStr);
    auto keyboard = KeyboardWinStrategy();
    keyboard.Write("This is a test run....");
}
