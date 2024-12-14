cmake_minimum_required(VERSION 3.10)

# Set the project name
project(R-Type)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define binary names for game client and server
set(GAME_ENGINE_BINARY "R-Type")

# Find SFML (make sure it's installed on your system)
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

#ADD ECS
add_subdirectory(ECS)

# Define game engine sources
set(SOURCES
    ${PROJECT_SOURCE_DIR}/GameEngine/src/Entity/Bullet.cpp
    ${PROJECT_SOURCE_DIR}/GameEngine/src/Entity/Obstacles.cpp
    ${PROJECT_SOURCE_DIR}/GameEngine/src/Entity/Player.cpp

    ${PROJECT_SOURCE_DIR}/GameEngine/src/Layers/Game.cpp
    ${PROJECT_SOURCE_DIR}/GameEngine/src/Layers/Menu.cpp
    ${PROJECT_SOURCE_DIR}/GameEngine/src/Layers/Lobby.cpp

    ${PROJECT_SOURCE_DIR}/GameEngine/src/Object/Background.cpp
    ${PROJECT_SOURCE_DIR}/GameEngine/src/Object/Buttons.cpp
    ${PROJECT_SOURCE_DIR}/GameEngine/src/Object/Icons.cpp
    ${PROJECT_SOURCE_DIR}/GameEngine/src/Object/Input.cpp
    ${PROJECT_SOURCE_DIR}/GameEngine/src/Object/Text.cpp

    ${PROJECT_SOURCE_DIR}/GameEngine/src/ManageElement.cpp
    ${PROJECT_SOURCE_DIR}/GameEngine/src/ManageScene.cpp
    ${PROJECT_SOURCE_DIR}/GameEngine/src/main.cpp

)

# Define include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/ECS/components
    ${PROJECT_SOURCE_DIR}/ECS/systems
    ${PROJECT_SOURCE_DIR}/GameEngine/include/Entity
    ${PROJECT_SOURCE_DIR}/GameEngine/include/Layers
    ${PROJECT_SOURCE_DIR}/GameEngine/include/Object
    ${PROJECT_SOURCE_DIR}/GameEngine/include
)
# Add game engine library
add_library(GameEngine STATIC ${SOURCES})

#Add ECS library
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

# Optionally: Set up for client/server if needed
add_executable(${GAME_ENGINE_BINARY} ${SOURCES})
target_link_libraries(${GAME_ENGINE_BINARY} GameEngine)

# Include directories for the game engine
target_include_directories(GameEngine
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
