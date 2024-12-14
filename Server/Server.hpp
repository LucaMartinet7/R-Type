/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** server
*/

#pragma once

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

#include <iostream>

#include "Network/Packet.hpp"


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
        Server(boost::asio::io_context& io_context, short port, ThreadSafeQueue<Network::Packet> &packetQueue);
        /**
         * @brief Destroys the Server object.
         */
        ~Server();
        void handle_receive(const boost::system::error_code &error, std::size_t bytes_transferred);

    private:
        using PacketHandler = std::function<void(const std::vector<std::string>&)>;
        std::unordered_map<std::string, PacketHandler> packet_handlers_;

        void handle_connected_packet(const std::vector<std::string>& segments);
        void handle_disconnected_packet(const std::vector<std::string>& segments);
        void handle_game_start_packet(const std::vector<std::string>& segments);

        void initialize_packet_handlers();
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

        boost::asio::ip::udp::socket socket_; ///< The UDP socket used for communication.
        boost::asio::ip::udp::endpoint remote_endpoint_; ///< The remote endpoint from which data is received.
        std::array<char, MAX_LENGTH> recv_buffer_; ///< Buffer to store received data.

        ThreadSafeQueue<Network::Packet> &m_packetQueue;
        std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>> packet_handlers_;
    };
}