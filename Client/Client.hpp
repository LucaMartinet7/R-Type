/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** Client
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Registry.hpp"
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/array.hpp>
#include <iostream>
#include <array>
#include <thread>
#include <csignal>

#define MAX_LENGTH 1024

namespace RType {

    /*!
     * @class Client
     * @brief Represents the R-Type game client.
     * @details This class manages network communication, rendering, and input handling for the R-Type game client.
     */
    class Client {
    public:
        /*!
         * @brief Constructs a new Client object.
         * @param io_context The Boost.Asio IO context for networking operations.
         * @param host The server hostname or IP address.
         * @param server_port The port on which the server is listening.
         * @param client_port The local port for the client.
         */
        Client(boost::asio::io_context& io_context, const std::string& host, short server_port, short client_port);

        /*!
         * @brief Destroys the Client object and cleans up resources.
         */
        ~Client();

        /*!
         * @brief Sends a message to the server asynchronously.
         * @param message The message to send.
         */
        void send(const std::string& message);

        /*!
         * @brief Starts asynchronous reception of messages from the server.
         */
        void start_receive();

        /*!
         * @brief Sends a disconnect packet to the server.
         * @details This method is used to notify the server when the client exits.
         */
        void sendExitPacket() {
            std::string exit_message = "DISCONNECTED";
            send(exit_message);
        }

        /*!
         * @brief Starts the main execution loop of the client.
         * @details This method handles rendering, input processing, and communication with the server.
         */
        void run();

    private:
        /*!
         * @brief Handles the receipt of a message from the server.
         * @param error The error code, if any occurred.
         * @param bytes_transferred The number of bytes received.
         */
        void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred);

        /*!
         * @brief Handles the completion of sending a message to the server.
         * @param error The error code, if any occurred.
         * @param bytes_transferred The number of bytes sent.
         */
        void handle_send(const boost::system::error_code& error, std::size_t bytes_transferred);

        /*!
         * @brief Runs the Boost.Asio IO context for asynchronous operations.
         */
        void run_receive();

        /*!
         * @brief Renders the game screen and updates the game state.
         */
        void render();

        /*!
         * @brief Processes user input and handles events from the game window.
         */
        void processEvents();

        boost::asio::ip::udp::socket socket_; /*!< The UDP socket used for communication. */
        boost::asio::ip::udp::endpoint server_endpoint_; /*!< The endpoint of the server. */
        std::array<char, MAX_LENGTH> recv_buffer_; /*!< The buffer for receiving data. */
        std::thread receive_thread_; /*!< The thread handling asynchronous message reception. */
        boost::asio::io_context& io_context_; /*!< The Boost.Asio IO context for networking. */
        sf::RenderWindow window; /*!< The SFML window for rendering the game. */
        bool gameStarted; /*!< Flag indicating whether the game has started. */
        Registry registry; /*!< The registry for managing game entities and components. */
        Registry::Entity entity_player; /*!< The entity representing the player. */
    };
}
