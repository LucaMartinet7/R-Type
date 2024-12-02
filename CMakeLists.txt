cmake_minimum_required(VERSION 3.10)

# Set the project name
project(RType)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CLIENT_BINARY "r-type_client")
set(SERVER_BINARY "r-type_server")

# Define the macro for Boost bind global placeholders
add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)

# fetch
include(FetchContent)

FetchContent_Declare(
  asio
  GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
  GIT_TAG asio-1-18-0
)
FetchContent_MakeAvailable(asio)
add_library(asio INTERFACE)

add_executable(${SERVER_BINARY}
                  Server/main.cpp
                  Server/Server.cpp
                  Server/Server.hpp
                  Server/Errors/Throws.hpp
                  )
target_link_libraries(${SERVER_BINARY} asio pthread)
