cmake_minimum_required(VERSION 3.10.0)
project(Orion VERSION 0.1.0 LANGUAGES C CXX)

add_executable(
    Orion 
    main.cpp
    include/Logger/ILogger.h
    include/Logger/LoggerBase.h
    include/Config/Limits.h
    src/Logger/LoggerBase.cpp
)

include(CTest)
enable_testing()

