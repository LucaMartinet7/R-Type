cmake_minimum_required(VERSION 3.14)

# Set the project name
project(R-Type)

# Specify the C++ standard (C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CLIENT_BINARY "r-type_client")
set(SERVER_BINARY "r-type_server")
set(GAME_ENGINE_BINARY "r-type_game_engine")

add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)

# ECS Subdirectory
add_subdirectory(ECS)

# FetchContent setup

include(FetchContent)

# Fetch Boost

FetchContent_Declare(
    Boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.83.0/boost-1.83.0.tar.xz
    DOWNLOAD_NAME boost_1_83_0.tar.gz
    DOWNLOAD_NO_PROGRESS TRUE
    DOWNLOAD_EXTRACT_TIMESTAMP ON
)


set(BOOST_INCLUDE_LIBRARIES
  asio
  iostreams
  assert
  align
  array
  bind
  coroutine
  config
  context
  core
  chrono
  date_time
  exception
  filesystem
  function
  move
  system
  smart_ptr
  throw_exception
  type_traits
  utility
)


FetchContent_MakeAvailable(Boost)

# Fetch SFML
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1
)


set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_AUDIO ON CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK ON CACHE BOOL "" FORCE)


FetchContent_MakeAvailable(SFML)

# Add the Server executable
add_executable(${SERVER_BINARY}
    Server/main.cpp
    Server/Server.cpp
    Server/Server.hpp
    Server/Errors/Throws.hpp
    Server/Network/PacketHandler.cpp
    Server/Network/PacketHandler.hpp
    Server/ClientRegister.hpp
)

target_link_libraries(${SERVER_BINARY}
    PRIVATE
        # Boost
        Boost::asio
        Boost::system
        Boost::iostreams

        # SFML (if the server needs SFML functionalities)
        sfml-system
        sfml-network
)

# Add the Client executable
add_executable(${CLIENT_BINARY}
    Client/main.cpp
    Client/Client.cpp
    Client/Client.hpp
    Server/Errors/Throws.hpp
    Server/Network/PacketType.hpp
)

target_link_libraries(${CLIENT_BINARY}
    PRIVATE
        # Boost
        Boost::asio
        Boost::system
        Boost::iostreams

        # SFML
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
)
