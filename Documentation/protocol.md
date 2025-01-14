## README: R-Type Protocol

## Def
This document defines the communication protocol between the server and clients in **R-Type**. The server maintains the game state, sending updates to clients, while clients relay player inputs and react to server commands. The `PacketType` enum categorizes packets for streamlined communication.

---

## Table of Contents
1. [Packet Structure](#packet-structure)
2. [Connection](#connection)
3. [Gameplay Flow](#gameplay-flow)
    - [Creating a Game](#creating-a-game)
    - [Joining a Game](#joining-a-game)
4. [Gameplay Communication](#gameplay-communication)
    - [Server-to-Client Packets](#server-to-client-packets)
    - [Client-to-Server Packets](#client-to-server-packets)
5. [Payload Details](#payload-details)
6. [Error Handling](#error-handling)

---

## Packet Structure
Each packet exchanged between the server and clients consists of:
- **Type (`PacketType`)**: Specifies the packet category (1 byte).
- **Client ID (`uint32_t`)**: Identifies the client (4 bytes).
- **Payload**: A 256-byte array for additional data.

---

## Connection
1. Clients connect to the server at the designated endpoint and port (e.g., `12345`).
2. Upon connection, the server sends a `CONNECTED` packet to confirm.

---

## Gameplay Flow

### Creating a Game
1. Client sends a `GAME_START` packet to create a new game instance.
   - Payload: Optionally specify game settings (e.g., level or mode).
2. Server responds with a `LEADER_CHANGE` packet, assigning the client as the leader.

---

### Joining a Game
1. Client sends a `PLAYER_JOIN` packet to join an existing game instance.
   - Payload: Specify the game instance ID.
2. Server responds with a `CONNECTED` packet to confirm addition to the instance.

---

## Gameplay Communication

### Server-to-Client Packets
1. **Game State Updates**
   - **Packet Type**: `MAP_UPDATE`
   - **Payload**: Serialized game state (e.g., entity positions).
2. **Player Events**
   - **Packet Type**:
     - `PLAYER_MOVED` for movement.
     - `PLAYER_SHOOT` for firing.
     - `PLAYER_SCORE` for score updates.
   - **Payload**: Relevant player data.
3. **Enemy Events**
   - **Packet Type**:
     - `ENEMY_SPAWNED` for new enemy creation.
     - `ENEMY_MOVED` for movement.
     - `ENEMY_DEAD` for destruction.
   - **Payload**: Relevant enemy data.
4. **Game End**
   - **Packet Type**: `GAME_END`
   - **Payload**: Game outcome (e.g., victory or defeat).

---

### Client-to-Server Packets
1. **Player Actions**
   - **Packet Type**:
     - `PLAYER_MOVED` for directional input.
     - `PLAYER_SHOOT` for firing.
   - **Payload**: Input data (e.g., direction or action).
2. **Player Status**
   - **Packet Type**: `PLAYER_HIT`
   - **Payload**: Current player health.

---

## Payload Details

| **Packet Type**      | **Payload Format**                                         | **Description**                                |
|-----------------------|-----------------------------------------------------------|------------------------------------------------|
| `CONNECTED`          | None                                                      | Sent by the server to confirm connection.      |
| `GAME_START`         | `[LEVEL_ID]`                                              | Start a new game with the specified level.     |
| `PLAYER_JOIN`        | `[INSTANCE_ID]`                                           | Join the specified game instance.             |
| `PLAYER_MOVED`       | `[X, Y, DIRECTION]`                                       | Update player position or direction.          |
| `PLAYER_SHOOT`       | `[PROJECTILE_TYPE, DIRECTION]`                            | Player fires a projectile.                    |
| `ENEMY_SPAWNED`      | `[TYPE, X, Y]`                                            | Spawn a new enemy at a specific position.      |
| `MAP_UPDATE`         | `[ENTITY_LIST]`                                           | Full game state update for all entities.       |
| `GAME_END`           | `[RESULT]`                                                | End of game with the outcome.                 |

---

## Error Handling
1. Malformed or unauthorized packets result in a `DISCONNECTED` response.
2. Upon receiving a `DISCONNECTED` packet, clients should terminate the connection and display an error message.

---
