cmake_minimum_required(VERSION 3.10.0)
project(Orion VERSION 0.1.0 LANGUAGES C CXX)

add_executable(
    Orion 
    main.cpp
    include/Logger/ILogger.h
    include/Logger/LoggerBase.h
    include/Config/Limits.h
    src/Logger/LoggerBase.cpp
    include/Command/Visitor/CommandVisitor.h
    include/Command/ICommand.h
    include/Command/Commands/SavePointCommand.h
    src/Command/Commands/SavePointCommand.cpp
    include/Command/CommandBase.h
    src/Command/CommandBase.cpp
    include/Command/Commands/SavePointMoveCommand.h
    src/Command/Commands/SavePointMoveCommand.cpp
    include/Keyboard/IKeyboard.h
    include/Keyboard/KeyboardWinStrategy.h
    src/Keyboard/KeyboardWinStrategy.cpp
)

include(CTest)
enable_testing()

