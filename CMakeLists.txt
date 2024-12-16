cmake_minimum_required(VERSION 3.10)

# Set the project name
project(R-Type)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define binary names for game client and server
set(CLIENT_BINARY "r-type_client")
set(SERVER_BINARY "r-type_server")
set(GAME_ENGINE_BINARY "r-type_game_engine")

# Define the macro for Boost bind global placeholders
add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)

# Find SFML (make sure it's installed on your system)
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

# Add ECS
add_subdirectory(ECS)

# fetch
include(FetchContent)

FetchContent_Declare(
  asio
  GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
  GIT_TAG asio-1-18-0
)
FetchContent_MakeAvailable(asio)
add_library(asio INTERFACE)

# Define game engine sources
set(SOURCES
    ${PROJECT_SOURCE_DIR}/GameEngine/src/Game.cpp
    ${PROJECT_SOURCE_DIR}/GameEngine/src/main.cpp
)

# Define include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/ECS/components
    ${PROJECT_SOURCE_DIR}/ECS/systems
    ${PROJECT_SOURCE_DIR}/GameEngine/include/Entity
    ${PROJECT_SOURCE_DIR}/GameEngine/include/Layer
    ${PROJECT_SOURCE_DIR}/GameEngine/include/
    ${PROJECT_SOURCE_DIR}/Server/Network
)

# Add game engine library
add_library(GameEngine STATIC ${SOURCES})

# Add ECS library
target_link_libraries(GameEngine ECSLib)

# Link dependencies to the game engine
target_link_libraries(GameEngine
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

# Specify output directories
set_target_properties(GameEngine PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

# Add game engine executable
add_executable(${GAME_ENGINE_BINARY} ${SOURCES})
target_link_libraries(${GAME_ENGINE_BINARY} GameEngine)

# Include directories for the game engine
target_include_directories(GameEngine
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

# Add server executable
add_executable(${SERVER_BINARY}
                  Server/main.cpp
                  Server/Server.cpp
                  Server/Server.hpp
                  Server/Errors/Throws.hpp
                  Server/Network/PacketHandler.cpp
                  )

# Add client executable
add_executable(${CLIENT_BINARY}
                  Client/main.cpp
                  Client/Client.cpp
                  Client/Client.hpp
                  Server/Errors/Throws.hpp
                  )

# Link game engine and asio to server
target_link_libraries(${SERVER_BINARY} GameEngine asio)

# Link game engine and asio to client
target_link_libraries(${CLIENT_BINARY} GameEngine asio)