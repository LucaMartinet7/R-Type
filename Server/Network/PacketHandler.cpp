/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** PacketHandler
*/

#include "PacketHandler.hpp"
#include <iostream>

using namespace Network;

// Constructor
PacketHandler::PacketHandler(ThreadSafeQueue<Network::Packet> &queue)
: m_queue(queue)
{
    initializeHandlers();
}

PacketHandler::~PacketHandler() {
    stop();
}

void PacketHandler::start() {
    m_running = true;
    m_thread = std::thread(&PacketHandler::processPackets, this);
}

void PacketHandler::stop() {
    m_running = false;
    if (m_thread.joinable())
        m_thread.join();
}

void PacketHandler::processPackets() {
    while (m_running) {
        Network::Packet packet = m_queue.pop();
        handlePacket(packet);
    }
}

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

void PacketHandler::handlePacket(const Network::Packet &packet) {
    auto it = m_handlers.find(packet.type);
    if (it != m_handlers.end()) {
        it->second(packet);
    } else {
        std::cout << "[PacketHandler] Received unknown packet type." << std::endl;
    }
}

void PacketHandler::handleNone(const Network::Packet &packet)
{
    std::cout << "[PacketHandler] Handling NONE packet." << std::endl;
    std::cout << "Data: " << std::get<Network::StartData>(packet.data).id << std::endl;
}

void PacketHandler::reqConnect(const Network::Packet &packet)
{
    std::cout << "[PacketHandler] Handling CONNECTED packet." << std::endl;
    std::cout << "Data: " << std::get<Network::ReqConnect>(packet.data).id << std::endl;
}

void PacketHandler::handleDisconnected(const Network::Packet &packet)
{
    std::cout << "[PacketHandler] Handling DISCONNECTED packet." << std::endl;
    std::cout << "Data: " << std::get<Network::DisconnectData>(packet.data).id << std::endl;
}

void PacketHandler::handleGameStart(const Network::Packet &packet)
{
    std::cout << "[PacketHandler] Handling GAME_START packet." << std::endl;
    std::cout << "Data: " << std::get<Network::StartData>(packet.data).id << std::endl;
}

void PacketHandler::handlePlayerDead(const Network::Packet &packet)
{
    std::cout << "[PacketHandler] Handling PLAYER_DEAD packet." << std::endl;
    std::cout << "Data: " << std::get<Network::DeathData>(packet.data).id << std::endl;
}

void PacketHandler::handlePlayerJoin(const Network::Packet &packet)
{
    std::cout << "[PacketHandler] Handling PLAYER_JOIN packet." << std::endl;
    std::cout << "Data: " << std::get<Network::JoinData>(packet.data).id << std::endl;
}

void PacketHandler::handlePlayerShoot(const Network::Packet &packet)
{
    std::cout << "[PacketHandler] Handling PLAYER_SHOOT packet." << std::endl;
    std::cout << "Data: " << std::get<Network::EntityData>(packet.data).id << std::endl;
}

void PacketHandler::handlePlayerHit(const Network::Packet &packet)
{
    std::cout << "[PacketHandler] Handling PLAYER_HIT packet." << std::endl;
    std::cout << "Data: " << std::get<Network::EntityData>(packet.data).id << std::endl;
}

void PacketHandler::handlePlayerScore(const Network::Packet &packet)
{
    std::cout << "[PacketHandler] Handling PLAYER_SCORE packet." << std::endl;
    std::cout << "Data: " << std::get<Network::ScoreData>(packet.data).score << std::endl;
}

void PacketHandler::handleEnemySpawned(const Network::Packet &packet)
{
    std::cout << "[PacketHandler] Handling ENEMY_SPAWNED packet." << std::endl;
    std::cout << "Data: " << std::get<Network::EntityData>(packet.data).id << std::endl;
}

void PacketHandler::handleEnemyDead(const Network::Packet &packet)
{
    std::cout << "[PacketHandler] Handling ENEMY_DEAD packet." << std::endl;
    std::cout << "Data: " << std::get<Network::DeathData>(packet.data).id << std::endl;
}

void PacketHandler::handleEnemyMoved(const Network::Packet &packet)
{
    std::cout << "[PacketHandler] Handling ENEMY_MOVED packet." << std::endl;
    std::cout << "Data: " << std::get<Network::EntityData>(packet.data).id << std::endl;
}

void PacketHandler::handleEnemyShoot(const Network::Packet &packet)
{
    std::cout << "[PacketHandler] Handling ENEMY_SHOOT packet." << std::endl;
    std::cout << "Data: " << std::get<Network::EntityData>(packet.data).id << std::endl;
}

void PacketHandler::handleEnemyLifeUpdate(const Network::Packet &packet)
{
    std::cout << "[PacketHandler] Handling ENEMY_LIFE_UPDATE packet." << std::endl;
    std::cout << "Data: " << std::get<Network::EntityData>(packet.data).id << std::endl;
}

void PacketHandler::handleMapUpdate(const Network::Packet &packet)
{
    std::cout << "[PacketHandler] Handling MAP_UPDATE packet." << std::endl;
    std::cout << "Data: " << std::get<Network::EntityData>(packet.data).id << std::endl;
}

void PacketHandler::handleGameEnd(const Network::Packet &packet)
{
    std::cout << "[PacketHandler] Handling GAME_END packet." << std::endl;
    std::cout << "Data: " << std::get<Network::EntityData>(packet.data).id << std::endl;
}

void PacketHandler::handlePlayerMoved(const Network::Packet &packet)
{
    std::cout << "[PacketHandler] Handling PLAYER_MOVED packet." << std::endl;
    std::cout << "Data: " << std::get<Network::PositionData>(packet.data).x << std::endl;
}
