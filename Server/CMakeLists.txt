cmake_minimum_required(VERSION 3.14)
project(R-Type_Server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)

# Local includes
include_directories(
    ${CMAKE_SOURCE_DIR}/R-Type/include
    ${CMAKE_SOURCE_DIR}/R-Type/include/Entity
    ${CMAKE_SOURCE_DIR}/Server/Network
    ${CMAKE_SOURCE_DIR}/ECS
    ${CMAKE_SOURCE_DIR}/ECS/systems
    ${CMAKE_SOURCE_DIR}/ECS/components
)

# The Server library sources
set(SERVER_SOURCES
    Server.cpp
    Server.hpp
    ClientRegister.hpp
    Errors/Throws.hpp
    Network/PacketHandler.cpp
    Network/PacketHandler.hpp
    Network/Data.hpp
    Network/Packet.hpp
    Network/Packet.cpp
    Network/PacketType.hpp
    Network/ThreadSafeQueue.hpp
)

add_library(ServerLib ${SERVER_SOURCES})

target_link_libraries(ServerLib
    R-Type
    Boost::Boost
    SFML::SFML
    ECSLib
)
