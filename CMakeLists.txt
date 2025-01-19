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

# Define the macro for Boost bind global placeholders
add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)

include_directories(
    ${CMAKE_SOURCE_DIR}/R-Type/include
    ${CMAKE_SOURCE_DIR}/R-Type/include/Entity/
    ${CMAKE_SOURCE_DIR}/Network/include
    ${CMAKE_SOURCE_DIR}/Server/include
    ${CMAKE_SOURCE_DIR}/ECS/
    ${CMAKE_SOURCE_DIR}/ECS/systems/
    ${CMAKE_SOURCE_DIR}/ECS/components/
    ${CMAKE_SOURCE_DIR}/Server/Errors/
    ${CMAKE_SOURCE_DIR}/Client/include/

)

# Find SFML (make sure it's installed on your system)
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

# Add ECS
add_subdirectory(ECS)

# fetch
include(FetchContent)

FetchContent_Declare(
    Boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.83.0/boost-1.83.0.tar.xz
    DOWNLOAD_NAME boost_1_83_0.tar.gz
    DOWNLOAD_NO_PROGRESS TRUE
)

FetchContent_MakeAvailable(Boost)

# Add server executable
add_executable(${SERVER_BINARY}
    Server/main.cpp
    Server/src/Server.cpp
    Network/src/PacketHandler.cpp
    R-Type/src/GameState.cpp
    R-Type/src/AGame.cpp
    R-Type/src/PlayerAction.cpp
    R-Type/src/Entity/Player.cpp
    R-Type/src/Entity/Enemy.cpp
    R-Type/src/Entity/Bullet.cpp
    R-Type/src/Entity/Boss.cpp
)

# Add client executable
add_executable(${CLIENT_BINARY}
    Client/main.cpp
    Client/src/Client.cpp
)

# Link the Boost libraries provided by FetchContent
target_link_libraries(${SERVER_BINARY} Boost::asio Boost::system)
target_link_libraries(${CLIENT_BINARY} Boost::asio Boost::system)
target_link_libraries(${SERVER_BINARY} sfml-graphics sfml-window sfml-system sfml-audio)
target_link_libraries(${CLIENT_BINARY} sfml-graphics sfml-window sfml-system sfml-audio)