#pragma once

#include <thread>
#include <atomic>
#include <functional>
#include <unordered_map>
#include "ThreadSafeQueue.hpp"
#include "Packet.hpp"
#include "PacketType.hpp"

class PacketHandler {
public:
    PacketHandler(ThreadSafeQueue<Network::Packet> &queue);
    ~PacketHandler();

    void start();
    void stop();

private:
    void processPackets();
    void handlePacket(const Network::Packet &packet);
    void initializeHandlers();

    // Static handler functions for each packet type
    static void handleNone(const Network::Packet &packet);
    static void handleConnected(const Network::Packet &packet);
    static void handleDisconnected(const Network::Packet &packet);
    static void handleGameStart(const Network::Packet &packet);
    static void handlePlayerDead(const Network::Packet &packet);
    static void handlePlayerJoin(const Network::Packet &packet);
    static void handlePlayerShoot(const Network::Packet &packet);
    static void handlePlayerHit(const Network::Packet &packet);
    static void handlePlayerScore(const Network::Packet &packet);
    static void handleEnemySpawned(const Network::Packet &packet);
    static void handleEnemyDead(const Network::Packet &packet);
    static void handleEnemyMoved(const Network::Packet &packet);
    static void handleEnemyShoot(const Network::Packet &packet);
    static void handleEnemyLifeUpdate(const Network::Packet &packet);
    static void handleMapUpdate(const Network::Packet &packet);
    static void handleGameEnd(const Network::Packet &packet);
    static void handlePlayerMoved(const Network::Packet &packet);

    ThreadSafeQueue<Network::Packet> &m_queue;
    std::thread m_thread;
    std::atomic<bool> m_running{false};

    std::unordered_map<Network::PacketType, void(*)(const Network::Packet&)> m_handlers;
};
