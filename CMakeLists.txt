cmake_minimum_required(VERSION 3.10)

# Set the project name
project(game_engine)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define binary names for game client and server
set(GAME_ENGINE_BINARY "game_engine")

# Find SFML (make sure it's installed on your system)
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

# Define game engine sources
set(SOURCES
    # Core Game Engine files
    game_engine/ManageDisplay.cpp
    game_engine/ManageLayer.cpp

    # Display sources
    game_engine/Display/Game.cpp

    # Object sources
    game_engine/Object/Background.cpp
    game_engine/Object/Buttons.cpp
    game_engine/Object/Icons.cpp
    game_engine/Object/Input.cpp
    game_engine/Object/Text.cpp

    # Entity sources
    game_engine/Entity/Player.cpp
    game_engine/Entity/Obstacles.cpp
    game_engine/Entity/Projectile.cpp
)

# Add game engine library
add_library(game_engine STATIC ${SOURCES})

# Link dependencies to the game engine
target_link_libraries(game_engine
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

# Specify output directories
set_target_properties(game_engine PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

# Optionally: Set up for client/server if needed
add_executable(${GAME_ENGINE_BINARY} ${SOURCES})
target_link_libraries(${GAME_ENGINE_BINARY} game_engine)

# Include directories for the game engine
target_include_directories(game_engine
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
