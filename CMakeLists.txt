cmake_minimum_required(VERSION 3.10)

# Set the project name
project(R-Type)
project(RType)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CLIENT_BINARY "r-type_client")
set(SERVER_BINARY "r-type_server")

# Define the macro for Boost bind global placeholders
add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

# fetch
include(FetchContent)

FetchContent_Declare(
  asio
  GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
  GIT_TAG asio-1-18-0
)
FetchContent_MakeAvailable(asio)
add_library(asio INTERFACE)
add_subdirectory(ECS)

include_directories(
    ${PROJECT_SOURCE_DIR}/ECS/components
    ${PROJECT_SOURCE_DIR}/ECS/systems
    ${PROJECT_SOURCE_DIR}/GameEngine/include/Entity
    ${PROJECT_SOURCE_DIR}/Server/Network
)

add_executable(${SERVER_BINARY}
                  Server/main.cpp
                  Server/Server.cpp
                  Server/Server.hpp
                  Server/Errors/Throws.hpp
                  Server/Network/PacketHandler.cpp
                  )

add_executable(${CLIENT_BINARY}
                  Client/main.cpp
                  Client/Client.cpp
                  Client/Client.hpp
                  Server/Errors/Throws.hpp
                  )

target_link_libraries(${SERVER_BINARY} asio)
target_link_libraries(${CLIENT_BINARY} asio
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)
