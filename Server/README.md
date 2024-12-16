# R-Type Server

The **R-Type Server** is a high-performance game server written in C++ for handling multiplayer interactions in the R-Type network game. It uses the Boost.Asio library for asynchronous UDP communication and provides robust packet processing capabilities. This server forms the backbone of the R-Type project, managing client connections, player actions, and game states.

---

## Key Concepts

- **Asynchronous Networking**: Leverages Boost.Asio for non-blocking UDP communication.
- **Thread-Safe Packet Queue**: Ensures smooth and safe multi-threaded packet processing.
- **Modular Packet Handling**: Utilizes a handler system to process various types of game events.
- **Scalability**: Designed to handle multiple clients efficiently while maintaining high performance.

---

## Project Structure

The project is organized into several key components to ensure modularity and maintainability:

### Source Files
- **`Server.cpp`**: Implements the core server logic, including handling client connections and broadcasting messages.
- **`main.cpp`**: Entry point of the application. Initializes the server and handles startup configurations.
- **`PacketHandler.cpp`**: Defines the processing logic for different packet types, such as player movements and game events.
- **`Packet.cpp`**: Handles the structure and serialization of network packets.

### Header Files
- **`Server.hpp`**: Declares the server class and its methods for handling networking.
- **`ThreadSafeQueue.hpp`**: Provides a thread-safe queue implementation for packet processing.
- **`PacketHandler.hpp`**: Declares methods for managing and handling game packets.
- **`PacketType.hpp`**: Defines enumerations for different packet types.
- **`Data.hpp`**: Includes data structures for packet payloads and game state representations.

### Networking
- Uses `boost::asio` for asynchronous networking.
- Manages client interactions via UDP sockets.

### Multi-threading
- Employs a `ThreadSafeQueue` to decouple packet receiving and processing for better performance.

---

## Key Features

1. **Client-Server Communication**: 
   - Handles incoming client requests such as connecting, disconnecting, and game actions.
   - Supports broadcasting messages to all connected clients.

2. **Dynamic Packet Handling**:
   - Processes packets for various game events like player movements, game start/end, and score updates.
   - Modular design for easy addition of new packet types.

3. **Error Handling**:
   - Catches and reports errors in port parsing, permission denial, and packet processing.

---

## Getting Started

### Prerequisites

- **C++ Compiler**: GCC 9.4+ or Clang 10+.
- **Boost Library**: Version 1.74 or newer.

---

## Technical Overview

### Architecture
The server uses a **reactor pattern** for asynchronous event handling, ensuring non-blocking operation for better scalability. The system is divided into:
- **Packet Receiver**: Listens for incoming UDP packets and queues them for processing.
- **Packet Handler**: Processes packets based on their type using a modular handler system.

### Packet Types
Supported packet types include:
- `REQCONNECT` - Client connection requests.
- `PLAYER_MOVED` - Updates player positions.
- `GAME_START`, `GAME_END` - Start and end game events.
- `DISCONNECTED` - Client disconnection notifications.

---
