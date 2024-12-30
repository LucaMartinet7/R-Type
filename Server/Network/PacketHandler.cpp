/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** PacketHandler
*/

#include "PacketHandler.hpp"
#include <iostream>
#include <boost/algorithm/string.hpp>

using namespace Network;

/*!
 * @brief Constructs a PacketHandler object.
 * @param queue Reference to the thread-safe queue holding incoming packets.
 * @details Initializes the handler map for processing different packet types.
 */
PacketHandler::PacketHandler(ThreadSafeQueue<Network::Packet> &queue)
: m_queue(queue)
{
    initializeHandlers();
}

/*!
 * @brief Destroys the PacketHandler object.
 * @details Ensures the processing thread is stopped and joined properly.
 */
PacketHandler::~PacketHandler() {
    stop();
}

/*!
 * @brief Starts the packet processing thread.
 */
void PacketHandler::start() {
    m_running = true;
    m_thread = std::thread(&PacketHandler::processPackets, this);
}

/*!
 * @brief Stops the packet processing thread.
 * @details Signals the thread to stop and waits for it to join.
 */
void PacketHandler::stop() {
    m_running = false;
    if (m_thread.joinable())
        m_thread.join();
}

/*!
 * @brief Main loop for processing packets from the queue.
 * @details Processes packets by retrieving them from the queue and delegating to the appropriate handler.
 */
void PacketHandler::processPackets() {
    while (m_running) {
        Network::Packet packet = m_queue.pop();
        handlePacket(packet);
    }
}

/*!
 * @brief Initializes the handler map with functions for each packet type.
 */
void PacketHandler::initializeHandlers() {
    m_handlers[Network::PacketType::NONE] = &PacketHandler::handleNone;
    m_handlers[Network::PacketType::REQCONNECT] = &PacketHandler::reqConnect;
    m_handlers[Network::PacketType::DISCONNECTED] = &PacketHandler::handleDisconnected;
    m_handlers[Network::PacketType::GAME_START] = &PacketHandler::handleGameStart;
    m_handlers[Network::PacketType::PLAYER_DEAD] = &PacketHandler::handlePlayerDead;
    m_handlers[Network::PacketType::PLAYER_JOIN] = &PacketHandler::handlePlayerJoin;
    m_handlers[Network::PacketType::PLAYER_SHOOT] = &PacketHandler::handlePlayerShoot;
    m_handlers[Network::PacketType::PLAYER_HIT] = &PacketHandler::handlePlayerHit;
    m_handlers[Network::PacketType::PLAYER_SCORE] = &PacketHandler::handlePlayerScore;
    m_handlers[Network::PacketType::ENEMY_SPAWNED] = &PacketHandler::handleEnemySpawned;
    m_handlers[Network::PacketType::ENEMY_DEAD] = &PacketHandler::handleEnemyDead;
    m_handlers[Network::PacketType::ENEMY_MOVED] = &PacketHandler::handleEnemyMoved;
    m_handlers[Network::PacketType::ENEMY_SHOOT] = &PacketHandler::handleEnemyShoot;
    m_handlers[Network::PacketType::ENEMY_LIFE_UPDATE] = &PacketHandler::handleEnemyLifeUpdate;
    m_handlers[Network::PacketType::MAP_UPDATE] = &PacketHandler::handleMapUpdate;
    m_handlers[Network::PacketType::GAME_END] = &PacketHandler::handleGameEnd;
    m_handlers[Network::PacketType::PLAYER_MOVED] = &PacketHandler::handlePlayerMoved;
}

/*!
 * @brief Delegates the processing of a packet to its corresponding handler.
 * @param packet The packet to handle.
 */
void PacketHandler::handlePacket(const Network::Packet &packet) {
    auto it = m_handlers.find(packet.type);
    if (it != m_handlers.end()) {
        it->second(packet);
    } else {
        std::cout << "[PacketHandler] Received unknown packet type." << std::endl;
    }
}

/*!
 * @brief Static handler for packets with no specific type.
 * @param packet The packet to handle.
 */
void PacketHandler::handleNone(const Network::Packet &packet) {
    std::cout << "[PacketHandler] Handled NONE packet." << std::endl;
}

/*!
 * @brief Static handler for REQCONNECT packets.
 * @param packet The packet to handle.
 */
void PacketHandler::reqConnect(const Network::Packet &packet) {
    std::cout << "[PacketHandler] Handled CONNECTED packet." << std::endl;
}

/*!
 * @brief Static handler for DISCONNECTED packets.
 * @param packet The packet to handle.
 */
void PacketHandler::handleDisconnected(const Network::Packet &packet) {
    std::cout << "[PacketHandler] Handled DISCONNECTED packet." << std::endl;
}

/*!
 * @brief Static handler for GAME_START packets.
 * @param packet The packet to handle.
 */
void PacketHandler::handleGameStart(const Network::Packet &packet) {
    std::cout << "[PacketHandler] Handled GAME_START packet." << std::endl;
}

/*!
 * @brief Static handler for PLAYER_DEAD packets.
 * @param packet The packet to handle.
 */
void PacketHandler::handlePlayerDead(const Network::Packet &packet) {
    std::cout << "[PacketHandler] Handled PLAYER_DEAD packet." << std::endl;
}

/*!
 * @brief Static handler for PLAYER_JOIN packets.
 * @param packet The packet to handle.
 */
void PacketHandler::handlePlayerJoin(const Network::Packet &packet) {
    std::cout << "[PacketHandler] Handled PLAYER_JOIN packet." << std::endl;
}

/*!
 * @brief Static handler for PLAYER_SHOOT packets.
 * @param packet The packet to handle.
 */
void PacketHandler::handlePlayerShoot(const Network::Packet &packet) {
    std::cout << "[PacketHandler] Handled PLAYER_SHOOT packet." << std::endl;
}

/*!
 * @brief Static handler for PLAYER_HIT packets.
 * @param packet The packet to handle.
 */
void PacketHandler::handlePlayerHit(const Network::Packet &packet) {
    std::cout << "[PacketHandler] Handled PLAYER_HIT packet." << std::endl;
}

/*!
 * @brief Static handler for PLAYER_SCORE packets.
 * @param packet The packet to handle.
 */
void PacketHandler::handlePlayerScore(const Network::Packet &packet) {
    std::cout << "[PacketHandler] Handled PLAYER_SCORE packet." << std::endl;
}

/*!
 * @brief Static handler for ENEMY_SPAWNED packets.
 * @param packet The packet to handle.
 */
void PacketHandler::handleEnemySpawned(const Network::Packet &packet) {
    std::cout << "[PacketHandler] Handled ENEMY_SPAWNED packet." << std::endl;
}

/*!
 * @brief Static handler for ENEMY_DEAD packets.
 * @param packet The packet to handle.
 */
void PacketHandler::handleEnemyDead(const Network::Packet &packet) {
    std::cout << "[PacketHandler] Handled ENEMY_DEAD packet." << std::endl;
}

/*!
 * @brief Static handler for ENEMY_MOVED packets.
 * @param packet The packet to handle.
 */
void PacketHandler::handleEnemyMoved(const Network::Packet &packet) {
    std::cout << "[PacketHandler] Handled ENEMY_MOVED packet." << std::endl;
}

/*!
 * @brief Static handler for ENEMY_SHOOT packets.
 * @param packet The packet to handle.
 */
void PacketHandler::handleEnemyShoot(const Network::Packet &packet) {
    std::cout << "[PacketHandler] Handled ENEMY_SHOOT packet." << std::endl;
}

/*!
 * @brief Static handler for ENEMY_LIFE_UPDATE packets.
 * @param packet The packet to handle.
 */
void PacketHandler::handleEnemyLifeUpdate(const Network::Packet &packet) {
    std::cout << "[PacketHandler] Handled ENEMY_LIFE_UPDATE packet." << std::endl;
}

/*!
 * @brief Static handler for MAP_UPDATE packets.
 * @param packet The packet to handle.
 */
void PacketHandler::handleMapUpdate(const Network::Packet &packet) {
    std::cout << "[PacketHandler] Handled MAP_UPDATE packet." << std::endl;
}

/*!
 * @brief Static handler for GAME_END packets.
 * @param packet The packet to handle.
 */
void PacketHandler::handleGameEnd(const Network::Packet &packet) {
    std::cout << "[PacketHandler] Handled GAME_END packet." << std::endl;
}

/*!
 * @brief Static handler for PLAYER_MOVED packets.
 * @param packet The packet to handle.
 */
void PacketHandler::handlePlayerMoved(const Network::Packet &packet) {
    std::cout << "[PacketHandler] Handled PLAYER_MOVED packet." << std::endl;
}
