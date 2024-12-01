/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** server
*/

#include "Server.hpp"
#include <boost/asio.hpp>


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
    start_receive();
}

RType::Server::~Server() {}

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
        [this](const boost::system::error_code& error, std::size_t bytes_transferred) {
            handle_receive(error, bytes_transferred);
        });
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
void RType::Server::handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error) {
        std::string message(recv_buffer_.data(), bytes_transferred);
        std::cout << "Received: " << message << " from " << remote_endpoint_ << std::endl;

        std::string response = "Message received!";
        socket_.async_send_to(
            boost::asio::buffer(response), remote_endpoint_,
            [](const boost::system::error_code& send_error, std::size_t bytes_sent) {
                if (!send_error) {
                    std::cout << "Response sent." << std::endl;
                }
            });
        start_receive();
    } else {
        std::cerr << "Error receiving: " << error.message() << std::endl;
    }
}

