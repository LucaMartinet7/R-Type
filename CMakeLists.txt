cmake_minimum_required(VERSION 3.10)

# Set the project name
project(RTypeECS)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directory for header files
include_directories(include)

# Add the source directory for main.cpp
add_executable(RTypeECS src/main.cpp)

# Add the systems directory for system implementations
file(GLOB SYSTEMS_SRC systems/*.cpp)
target_sources(RTypeECS PRIVATE ${SYSTEMS_SRC})

# Read .env file
file(READ "${CMAKE_SOURCE_DIR}/.env" ENV_CONTENTS)
string(REGEX MATCH "SFML_DIR=([^\\n]+)" _ ${ENV_CONTENTS})
set(SFML_DIR ${CMAKE_MATCH_1})

# Remove trailing quote from SFML_DIR
string(REGEX REPLACE "\"" "" SFML_DIR ${SFML_DIR})

# Find and link SFML
find_package(SFML COMPONENTS system window graphics REQUIRED)
target_link_libraries(RTypeECS sfml-system sfml-window sfml-graphics)