/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** PacketHandler
*/

#pragma once

#include <thread>
#include <atomic>
#include <functional>
#include <unordered_map>
#include "ThreadSafeQueue.hpp"
#include "Packet.hpp"
#include "PacketType.hpp"

namespace Network {

    /*!
     * @class PacketHandler
     * @brief Handles incoming packets and delegates processing to appropriate handlers.
     * @details This class processes packets from a thread-safe queue, determines their type, 
     * and executes the corresponding static handler function.
     */
    class PacketHandler {
    public:
        /*!
         * @brief Constructs a new PacketHandler object.
         * @param queue Reference to the thread-safe queue holding incoming packets.
         */
        PacketHandler(ThreadSafeQueue<Network::Packet> &queue);

        /*!
         * @brief Destroys the PacketHandler object.
         * @details Ensures proper cleanup and stops the processing thread if it is running.
         */
        ~PacketHandler();

        /*!
         * @brief Starts the packet processing thread.
         */
        void start();

        /*!
         * @brief Stops the packet processing thread.
         */
        void stop();

    private:
        /*!
         * @brief Main loop for processing packets from the queue.
         */
        void processPackets();

        /*!
         * @brief Handles a single packet by delegating it to the appropriate handler.
         * @param packet The packet to handle.
         */
        void handlePacket(const Network::Packet &packet);

        /*!
         * @brief Initializes the packet handlers for each packet type.
         */
        void initializeHandlers();

        /*!
         * @brief Static handler for packets with no specific type.
         * @param packet The packet to handle.
         */
        static void handleNone(const Network::Packet &packet);

        /*!
         * @brief Static handler for REQCONNECT packets.
         * @param packet The packet to handle.
         */
        static void reqConnect(const Network::Packet &packet);

        /*!
         * @brief Static handler for DISCONNECTED packets.
         * @param packet The packet to handle.
         */
        static void handleDisconnected(const Network::Packet &packet);

        /*!
         * @brief Static handler for GAME_START packets.
         * @param packet The packet to handle.
         */
        static void handleGameStart(const Network::Packet &packet);

        /*!
         * @brief Static handler for PLAYER_DEAD packets.
         * @param packet The packet to handle.
         */
        static void handlePlayerDead(const Network::Packet &packet);

        /*!
         * @brief Static handler for PLAYER_JOIN packets.
         * @param packet The packet to handle.
         */
        static void handlePlayerJoin(const Network::Packet &packet);

        /*!
         * @brief Static handler for PLAYER_SHOOT packets.
         * @param packet The packet to handle.
         */
        static void handlePlayerShoot(const Network::Packet &packet);

        /*!
         * @brief Static handler for PLAYER_HIT packets.
         * @param packet The packet to handle.
         */
        static void handlePlayerHit(const Network::Packet &packet);

        /*!
         * @brief Static handler for PLAYER_SCORE packets.
         * @param packet The packet to handle.
         */
        static void handlePlayerScore(const Network::Packet &packet);

        /*!
         * @brief Static handler for ENEMY_SPAWNED packets.
         * @param packet The packet to handle.
         */
        static void handleEnemySpawned(const Network::Packet &packet);

        /*!
         * @brief Static handler for ENEMY_DEAD packets.
         * @param packet The packet to handle.
         */
        static void handleEnemyDead(const Network::Packet &packet);

        /*!
         * @brief Static handler for ENEMY_MOVED packets.
         * @param packet The packet to handle.
         */
        static void handleEnemyMoved(const Network::Packet &packet);

        /*!
         * @brief Static handler for ENEMY_SHOOT packets.
         * @param packet The packet to handle.
         */
        static void handleEnemyShoot(const Network::Packet &packet);

        /*!
         * @brief Static handler for ENEMY_LIFE_UPDATE packets.
         * @param packet The packet to handle.
         */
        static void handleEnemyLifeUpdate(const Network::Packet &packet);

        /*!
         * @brief Static handler for MAP_UPDATE packets.
         * @param packet The packet to handle.
         */
        static void handleMapUpdate(const Network::Packet &packet);

        /*!
         * @brief Static handler for GAME_END packets.
         * @param packet The packet to handle.
         */
        static void handleGameEnd(const Network::Packet &packet);

        /*!
         * @brief Static handler for PLAYER_MOVED packets.
         * @param packet The packet to handle.
         */
        static void handlePlayerMoved(const Network::Packet &packet);

        ThreadSafeQueue<Network::Packet> &m_queue; /*!< Reference to the queue of packets to process. */
        std::thread m_thread; /*!< Thread for processing packets. */
        std::atomic<bool> m_running{false}; /*!< Flag indicating whether the processing thread is running. */

        /*!
         * @brief Map of packet types to their respective handler functions.
         */
        std::unordered_map<Network::PacketType, void(*)(const Network::Packet&)> m_handlers;
    };
}
