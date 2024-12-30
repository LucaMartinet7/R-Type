/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** Data
*/

#pragma once

#define MAX_PLAYERS 2

#include <iostream>

namespace Network {
    extern "C"
    {
        /*!
         * @struct StartData
         * @brief Represents data for starting a game.
         */
        struct StartData {
        public:
            int id; /*!< Unique identifier for the start data. */
        };

        /*!
         * @struct JoinData
         * @brief Represents data for a player joining a game.
         */
        struct JoinData {
        public:
            int id; /*!< Unique identifier for the joining player. */
        };

        /*!
         * @struct ReqConnect
         * @brief Represents data for a connection request.
         */
        struct ReqConnect {
        public:
            int id; /*!< Unique identifier for the connection request. */
        };

        /*!
         * @struct PositionData
         * @brief Represents position data for an entity.
         */
        struct PositionData {
        public:
            std::string directions; /*!< Directions for the entity movement. */
            float x; /*!< X-coordinate of the entity. */
            float y; /*!< Y-coordinate of the entity. */
        };

        /*!
         * @struct PlayerPositionData
         * @brief Represents the positions of all players.
         */
        struct PlayerPositionData {
        public:
            PositionData pos[MAX_PLAYERS]; /*!< Array of player positions. */
        };

        /*!
         * @struct ScoreData
         * @brief Represents a player's score data.
         */
        struct ScoreData {
        public:
            int score; /*!< The player's score. */
        };

        /*!
         * @struct EntityData
         * @brief Represents data about an entity.
         */
        struct EntityData {
        public:
            int id; /*!< Unique identifier for the entity. */
            char type; /*!< Type of the entity. */
            PositionData pos; /*!< Position data for the entity. */
            float vx; /*!< Velocity in the X direction. */
            float vy; /*!< Velocity in the Y direction. */
        };

        /*!
         * @struct DisconnectData
         * @brief Represents data for a disconnect event.
         */
        struct DisconnectData {
        public:
            int id; /*!< Unique identifier for the disconnect event. */
        };

        /*!
         * @struct DeathData
         * @brief Represents data for an entity's death.
         */
        struct DeathData {
        public:
            int id; /*!< Unique identifier for the dead entity. */
            char reason; /*!< Reason for the entity's death. */
        };

        /*!
         * @struct BossData
         * @brief Represents data about a boss entity.
         */
        struct BossData {
        public:
            int id; /*!< Unique identifier for the boss. */
            PositionData pos; /*!< Position data for the boss. */
            int alive; /*!< Whether the boss is alive (1) or dead (0). */
        };
    }
}
