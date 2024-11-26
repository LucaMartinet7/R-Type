cmake_minimum_required(VERSION 3.10)

# Check for required packages
find_package(Asio REQUIRED)

if(NOT Asio_FOUND)
    message(FATAL_ERROR "Asio not found. Please install it using 'sudo apt-get install libasio-dev'")
endif()

# Set the project name
project(MyProject)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(MyProject main.cpp)

# Include directories
include_directories(include)

# Link libraries
# target_link_libraries(MyProject <library_name>)