cmake_minimum_required(VERSION 3.8)
project(Project)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Array.cpp
        Array.h
        BoolValue.cpp
        BoolValue.h
        JsonParser.cpp
        JsonParser.h
        main.cpp
        NullValue.cpp
        NullValue.h
        Number.cpp
        Number.h
        Object.cpp
        Object.h
        Pair.cpp
        Pair.h
        String.cpp
        String.h
        test1.txt
        Value.cpp
        Value.h)

add_executable(Project ${SOURCE_FILES})