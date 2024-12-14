/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** server
*/

#include "Server.hpp"
#include "Network/ThreadSafeQueue.hpp"
#include <iostream>
#include <boost/iostreams/stream.hpp>

using boost::asio::ip::udp;

/**
 * @brief Constructs a new Server object.
 *
 * This constructor initializes the UDP socket and starts the asynchronous
 * receive operation to handle incoming data.
 *
 * @param io_context The io_context object used for asynchronous operations.
 * @param port The port number on which the server will listen for incoming UDP packets.
 */
RType::Server::Server(boost::asio::io_context &io_context, short port, ThreadSafeQueue<Network::Packet> &packetQueue)
: socket_(io_context, udp::endpoint(udp::v4(), port)), m_packetQueue(packetQueue)
{
    start_receive();
}


RType::Server::~Server()
{
    socket_.close();
}

/**
 * @brief Starts an asynchronous receive operation.
 *
 * This function initiates an asynchronous receive operation to receive data
 * from a remote endpoint. When data is received, the provided handler function
 * is called to process the received data.
 */
void RType::Server::start_receive()
{
    socket_.async_receive_from(
        boost::asio::buffer(recv_buffer_), remote_endpoint_,
        boost::bind(&RType::Server::handle_receive, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

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
void RType::Server::handle_receive(const boost::system::error_code &error, std::size_t bytes_transferred)
{
    if (!error || error == boost::asio::error::message_size) {
        std::string received_data(recv_buffer_.data(), bytes_transferred);
        std::stringstream ss(received_data);
        std::string segment;
        std::vector<std::string> segments;
        while (std::getline(ss, segment, ';'))
            segments.push_back(segment);

        if (segments.empty()) {
            start_receive();
            return;
        }
        if (segments.size() < 2) {
            std::cerr << "Error: Received data does not contain enough segments." << std::endl;
            start_receive();
            return;
        }
        std::string packet_type_str = segments[0];
        std::string packet_data = segments[1];
        Network::Packet packet;
        std::cout << "Received packet type: " << packet_type_str << std::endl;
        std::cout << "Received packet data: " << packet_data << std::endl;
        if (packet_type_str == "REQCONNECT") {
            packet.data = Network::ReqConnect{0, {0}};
            packet.type = Network::PacketType::REQCONNECT;
        } else if (packet_type_str == "DISCONNECTED") {
            packet.data = Network::DisconnectData{0};
            packet.type = Network::PacketType::DISCONNECTED;
        } else if (packet_type_str == "GAME_START") {
            packet.data = Network::StartData{0};
            packet.type = Network::PacketType::GAME_START;
        } else if (packet_type_str == "PLAYER_JOIN") {
            packet.data = Network::JoinData{0};
            packet.type = Network::PacketType::PLAYER_JOIN;
        } else if (packet_type_str == "PLAYER_MOVED") {
            packet.data = Network::PositionData{0, 0};
            packet.type = Network::PacketType::PLAYER_MOVED;
        } else {
            std::cerr << "Unknown packet type: " << packet_type_str << std::endl;
            start_receive();
            return;
        }
        // Push the packet to the queue
        m_packetQueue.push(packet);

        start_receive();
    }
}

void RType::Server::send_to_client(const std::string& message, const udp::endpoint& client_endpoint)
{
    socket_.async_send_to(
        boost::asio::buffer(message), client_endpoint,
        [](const boost::system::error_code& error, std::size_t bytes_transferred) {
            if (!error) {
                std::cout << "Message sent to client." << std::endl;
            } else {
                std::cerr << "Error sending to client: " << error.message() << std::endl;
            }
        });
}