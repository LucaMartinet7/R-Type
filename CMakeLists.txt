cmake_minimum_required(VERSION 3.10)

# Set the project name
project(RtypeECS)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(RtypeECS
        ECS/src/main.cpp
)

# Include directories
target_include_directories(RtypeECS PRIVATE
        ECS/include/systems
        ECS/include/components
        ECS/include/utils
)

# Find and link SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(RtypeECS sfml-graphics sfml-window sfml-system)