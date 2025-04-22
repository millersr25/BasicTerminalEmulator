cmake_minimum_required(VERSION 3.10)

# Set the C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# used internally by CMake to identify your project
project(basicTerminalEmulator)

# Add the main executable
add_executable(terminalApp main.cpp mypipe.cpp utility.cpp terminal.cpp)
