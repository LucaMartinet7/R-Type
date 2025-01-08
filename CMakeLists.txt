cmake_minimum_required(VERSION 3.10)

# Set the project name
project(R-Type)

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
    Boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.83.0/boost-1.83.0.tar.xz
    DOWNLOAD_NAME boost_1_83_0.tar.gz
    DOWNLOAD_NO_PROGRESS TRUE
    CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=Release
        -DCONFIG=Release
    DOWNLOAD_EXTRACT_TIMESTAMP ON
)

FetchContent_MakeAvailable(Boost)

set(BOOST_RUNTIME_LINK static)
set(BOOST_INCLUDE_LIBRARIES
  asio
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
  function
  filesystem
  move
  system
  smart_ptr
  throw_exception
  type_traits
  utility
)

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

# Remove the find_package(Boost 1.83 REQUIRED COMPONENTS ...) line

add_executable(${SERVER_BINARY}
                  Server/main.cpp
                  Server/Server.cpp
                  Server/Server.hpp
                  Server/Errors/Throws.hpp
                  Server/Network/PacketHandler.cpp
                  Server/Network/PacketHandler.hpp
                  Server/ClientRegister.hpp
                  )

add_executable(${CLIENT_BINARY}
                  Client/main.cpp
                  Client/Client.cpp
                  Client/Client.hpp
                  Server/Errors/Throws.hpp
                  )

# Link the Boost libraries provided by FetchContent
target_link_libraries(${SERVER_BINARY} Boost::asio Boost::system)
target_link_libraries(${CLIENT_BINARY} Boost::asio Boost::system sfml-graphics sfml-window sfml-system sfml-audio)