/*
** PacketType
*/

#pragma once

#include <cstdint>

#include "Packet.hpp"

namespace Network {
    enum class PacketType : uint8_t {
        NONE = 0,
        CONNECTED = 1,
        DISCONNECTED,
        GAME_START,
        PLAYER_DEAD,
        PLAYER_JOIN,
        PLAYER_SHOOT,
        PLAYER_HIT,
        PLAYER_SCORE,
        ENEMY_SPAWNED,
        ENEMY_DEAD,
        ENEMY_MOVED,
        ENEMY_SHOOT,
        ENEMY_LIFE_UPDATE,
        MAP_UPDATE,
        GAME_END,
        LEADER_CHANGE,
        PLAYER_MOVED,
    };
}
