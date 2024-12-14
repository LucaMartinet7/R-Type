/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** server
*/

#include "Server.hpp"
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
RType::Server::Server(boost::asio::io_context &io_context, short port) : socket_(io_context, udp::endpoint(udp::v4(), port))
{
    initialize_packet_handlers();
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

void RType::Server::initialize_packet_handlers() {
    packet_handlers_["CONNECTED"] = std::bind(&Server::handle_connected_packet, this, std::placeholders::_1);
    packet_handlers_["DISCONNECTED"] = std::bind(&Server::handle_disconnected_packet, this, std::placeholders::_1);
    packet_handlers_["GAME_START"] = std::bind(&Server::handle_game_start_packet, this, std::placeholders::_1);
    // Add more packet types and handlers as needed
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

        std::cout << "segments: ";
        for (const auto &seg : segments) {
            std::cout << seg << " ";
        }
        std::cout << std::endl;

        std::string packet_type_str = segments[0];
        std::cout << "Received packet type: " << packet_type_str << std::endl; // Add this line
        auto it = packet_handlers_.find(packet_type_str);
        if (it != packet_handlers_.end()) {
            it->second(segments);
        } else {
            throw std::runtime_error("Invalid packet type: " + packet_type_str);
        }

        std::cout << "Received packet: " << received_data << std::endl;
    }
    start_receive();
}

void RType::Server::handle_connected_packet(const std::vector<std::string>& segments)
{
    std::cout << "Handling CONNECTED packet with segments: ";
    for (const auto& segment : segments) {
        std::cout << segment << " ";
    }
    std::cout << std::endl;

    Network::Packet packet;
    packet.type = Network::PacketType::CONNECTED;
    Network::ConnectData data;
    data.id = std::stoi(segments[1]);
    // data.player[0] = static_cast<char>(std::stoi(segments[2]));
    packet.data = data;
    std::cout << "Player connected with ID: " << data.id << " and Player ID: " << data.player << std::endl;
}

void RType::Server::handle_disconnected_packet(const std::vector<std::string>& segments)
{
    if (segments.size() < 2) {
        throw std::runtime_error("Invalid DISCONNECTED packet format");
    }
    Network::Packet packet;
    packet.type = Network::PacketType::DISCONNECTED;
    Network::DisconnectData data;
    data.id = std::stoi(segments[1]);
    packet.data = data;
    std::cout << "Player disconnected with ID: " << data.id << std::endl;
}

void RType::Server::handle_game_start_packet(const std::vector<std::string>& segments)
{
    if (segments.size() < 2) {
        throw std::runtime_error("Invalid GAME_START packet format");
    }
    Network::Packet packet;
    packet.type = Network::PacketType::GAME_START;
    Network::StartData data;
    data.id = std::stoi(segments[1]);
    packet.data = data;
    std::cout << "Game started with ID: " << data.id << std::endl;
    // Handle the rest of the packet data...
}
