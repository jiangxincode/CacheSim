cmake_minimum_required(VERSION 3.17)
project(CacheSim)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CacheSim
        base.cpp
        base.h
        CalcInfo.cpp
        CreateCache.cpp
        FileTest.cpp
        GetInput.cpp
        InitVariables.cpp
        LRU.cpp
        main.cpp
        PrintOutput.cpp)
