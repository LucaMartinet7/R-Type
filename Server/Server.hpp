/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** server
*/

#pragma once

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <map>

#include "Network/ThreadSafeQueue.hpp"
#include "Network/Packet.hpp"
#include "ClientRegister.hpp"
#include "GameState.hpp"

typedef std::map<uint32_t, ClientRegister> ClientList;

#define MAX_LENGTH 1024

using namespace boost::placeholders; // Used for Boost.Asio asynchronous operations to bind placeholders for callback functions

namespace RType {
    /**
     * @brief The Server class handles incoming UDP connections and processes received data.
     */
    class Server {
    public:
        /**
         * @brief Constructs a new Server object.
         *
         * This constructor initializes the UDP socket and starts the asynchronous
         * receive operation to handle incoming data.
         *
         * @param io_context The io_context object used for asynchronous operations.
         * @param port The port number on which the server will listen for incoming UDP packets.
         */
        Server(boost::asio::io_context& io_context, short port, ThreadSafeQueue<Network::Packet> &packetQueue, GameState& game);
        /**
         * @brief Destroys the Server object.
         */
        ~Server();
        void handle_receive(const boost::system::error_code &error, std::size_t bytes_transferred);
        void send_to_client(const std::string& message, const udp::endpoint& client_endpoint);
        void Broadcast(const std::string& message);
        void PacketFactory();
        Network::ReqConnect reqConnectData(udp::endpoint& client_endpoint);
        Network::DisconnectData disconnectData(udp::endpoint& client_endpoint);
        void handle_game_packet(const Network::Packet& packet, const udp::endpoint& client_endpoint);
        std::string createPacket(const Network::PacketType& type, const std::string& data);
        Network::Packet deserializePacket(const std::string& packet_str);
        const ClientList& getClients() const { return clients_; }
        const udp::endpoint& getRemoteEndpoint() const {
            return remote_endpoint_;
            }
    private:
        using PacketHandler = std::function<void(const std::vector<std::string>&)>;
        /**
         * @brief Starts an asynchronous receive operation.
         *
         * This function initiates an asynchronous receive operation to receive data
         * from a remote endpoint. When data is received, the provided handler function
         * is called to process the received data.
         */
        void start_receive();
        /**
         * @brief Handles the completion of an asynchronous receive operation.
         *
         * This function is called when data is received from a remote endpoint. It processes
         * the received data, optionally sends a response back to the client, and restarts
         * the asynchronous receive operation to handle the next incoming message.
         *
         * @param error The error code indicating the result of the receive operation.
         * @param bytes_transferred The number of bytes received.
         */

        uint32_t createClient(udp::endpoint& client_endpoint);

        udp::socket socket_; ///< The UDP socket used for communication.
        udp::endpoint remote_endpoint_; ///< The remote endpoint from which data is received.
        std::array<char, MAX_LENGTH> recv_buffer_; ///< Buffer to store received data.

        ThreadSafeQueue<Network::Packet> &m_packetQueue;
        std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>> packet_handlers_;
        std::unordered_map<Network::PacketType, void(*)(const Network::Packet&)> m_handlers;
        ClientList clients_;
        size_t _nbClients;
        GameState& _game;
    };
}