/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** Client
*/

#include "Packet.hpp"
#include "ThreadSafeQueue.hpp"
#include "Client.hpp"
#include "Projectile.hpp"
#include "Player.hpp"
#include "Position.hpp"
#include "DrawSystem.hpp"

using boost::asio::ip::udp;

/*!
 * @brief Constructs a new Client object.
 * @param io_context The Boost.Asio IO context used for networking operations.
 * @param host The hostname or IP address of the server.
 * @param server_port The port number of the server.
 * @param client_port The local port number for the client.
 */
RType::Client::Client(boost::asio::io_context& io_context, const std::string& host, short server_port, short client_port)
    : socket_(io_context, udp::endpoint(udp::v4(), client_port)), io_context_(io_context), window(sf::VideoMode(800, 600), "Rtype"), gameStarted(false)
{
    udp::resolver resolver(io_context);
    udp::resolver::query query(udp::v4(), host, std::to_string(server_port));
    server_endpoint_ = *resolver.resolve(query).begin();
    std::cout << "Connected to " << host << ":" << server_port << " from client port " << client_port << std::endl;
    start_receive();
    receive_thread_ = std::thread(&Client::run_receive, this);
}

/*!
 * @brief Destroys the Client object and cleans up resources.
 */
RType::Client::~Client()
{
    socket_.close();
    if (receive_thread_.joinable()) {
        receive_thread_.join();
    }
}

/*!
 * @brief Sends a message to the server asynchronously.
 * @param message The message to send.
 */
void RType::Client::send(const std::string& message)
{
    socket_.async_send_to(
        boost::asio::buffer(message), server_endpoint_,
        boost::bind(&Client::handle_send, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

/*!
 * @brief Starts asynchronous reception of messages from the server.
 */
void RType::Client::start_receive()
{
    socket_.async_receive_from(
        boost::asio::buffer(recv_buffer_), server_endpoint_,
        boost::bind(&RType::Client::handle_receive, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

/*!
 * @brief Handles the receipt of a message from the server.
 * @param error The error code, if any occurred.
 * @param bytes_transferred The number of bytes received.
 */
void RType::Client::handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error || error == boost::asio::error::message_size) {
        std::cout << "Received: " << std::string(recv_buffer_.data(), bytes_transferred) << std::endl;
        start_receive();
    } else {
        std::cerr << "Error receiving: " << error.message() << std::endl;
    }
}

/*!
 * @brief Handles the completion of sending a message to the server.
 * @param error The error code, if any occurred.
 * @param bytes_transferred The number of bytes sent.
 */
void RType::Client::handle_send(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error) {
        std::cout << "Message sent." << std::endl;
    } else {
        std::cerr << "Error sending: " << error.message() << std::endl;
    }
}

/*!
 * @brief Runs the Boost.Asio IO context for asynchronous operations.
 */
void RType::Client::run_receive()
{
    io_context_.run();
}

/*!
 * @brief Processes user input events from the SFML window.
 */
void RType::Client::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Right) {
                std::string message = "PLAYER_MOVED;RIGHT";
                send(message);
            }
            if (event.key.code == sf::Keyboard::Left) {
                std::string message = "PLAYER_MOVED;LEFT";
                send(message);
            }
            if (event.key.code == sf::Keyboard::Up) {
                std::string message = "PLAYER_MOVED;UP";
                send(message);
            }
            if (event.key.code == sf::Keyboard::Down) {
                std::string message = "PLAYER_MOVED;DOWN";
                send(message);
            }
        }
    }
}

/*!
 * @brief Renders the game window and updates the game state.
 */
void RType::Client::render() {
    std::string input(recv_buffer_.data());

    std::string type;
    std::string data;
    float new_x = 0.0, new_y = 0.0;

    size_t move = input.find("PLAYER_MOVED");
    if (move == std::string::npos) {
        return;
    }

    size_t delimiterPos = input.find(';');
    if (delimiterPos != std::string::npos) {
        type = input.substr(0, delimiterPos);
        data = input.substr(delimiterPos + 1);
    }

    size_t commaPos = data.find(',');
    if (commaPos != std::string::npos) {
        new_x = std::stof(data.substr(0, commaPos));
        new_y = std::stof(data.substr(commaPos + 1));
    }

    static bool player_created = false;
    if (!player_created) {
        Player player(registry, new_x, new_y);
        player_created = true;
    }

    window.clear();
    try {
        draw_system(registry, window, registry.get_components<Position>(), registry.get_components<Drawable>());
    } catch (const std::out_of_range& e) {
        std::cerr << "Error accessing components: " << e.what() << std::endl;
    }
    window.display();
}

/*!
 * @brief Main execution loop of the client.
 * @details Sends an initial connection request, processes events, renders the game,
 * and sends a disconnect message upon exit.
 */
void RType::Client::run() {
    send("REQCONNECT");
    while (window.isOpen()) {
        processEvents();
        render();
    }

    send("DISCONNECTED");
}
