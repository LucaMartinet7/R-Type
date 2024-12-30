/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** PacketType
*/

#pragma once

#include <cstdint>
#include "Packet.hpp"

namespace Network {
    /*!
     * @enum PacketType
     * @brief Enumerates the types of packets exchanged in the R-Type game.
     */
    enum class PacketType {
        NONE = 0, /*!< No specific packet type. */
        REQCONNECT = 1, /*!< Request to connect. */
        DISCONNECTED = 2, /*!< Disconnection event. */
        GAME_START = 3, /*!< Game start event. */
        PLAYER_DEAD = 4, /*!< Player death event. */
        PLAYER_JOIN = 5, /*!< Player joined the game. */
        PLAYER_SHOOT = 6, /*!< Player shooting event. */
        PLAYER_HIT = 7, /*!< Player hit event. */
        PLAYER_SCORE = 8, /*!< Player score update. */
        ENEMY_SPAWNED = 9, /*!< Enemy spawn event. */
        ENEMY_DEAD = 10, /*!< Enemy death event. */
        ENEMY_MOVED = 11, /*!< Enemy movement event. */
        ENEMY_SHOOT = 12, /*!< Enemy shooting event. */
        ENEMY_LIFE_UPDATE = 13, /*!< Enemy life update event. */
        MAP_UPDATE = 14, /*!< Map update event. */
        GAME_END = 15, /*!< Game end event. */
        PLAYER_MOVED = 17 /*!< Player movement event. */
    };
}
