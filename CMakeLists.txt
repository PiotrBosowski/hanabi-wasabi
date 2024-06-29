# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(HanabiWasabi VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(
    hanabi
    src/fuzzycard.cpp
    src/hanabi.cpp
    src/player.cpp
    src/main.cpp
)
