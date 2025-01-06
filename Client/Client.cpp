/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** Client
*/

#include "Client.hpp"

using boost::asio::ip::udp;

RType::Client::Client(boost::asio::io_context& io_context, const std::string& host, short server_port, short client_port)
    : socket_(io_context, udp::endpoint(udp::v4(), client_port)), io_context_(io_context)
{
    udp::resolver resolver(io_context);
    udp::resolver::query query(udp::v4(), host, std::to_string(server_port));
    server_endpoint_ = *resolver.resolve(query).begin();
    std::cout << "Connected to " << host << ":" << server_port << " from client port " << client_port << std::endl;

    start_receive();
    receive_thread_ = std::thread(&Client::run_receive, this);
}

RType::Client::~Client()
{
    socket_.close();
    if (receive_thread_.joinable()) {
        receive_thread_.join();
    }
}

void RType::Client::send(const std::string& message)
{
    socket_.async_send_to(
        boost::asio::buffer(message), server_endpoint_,
        boost::bind(&Client::handle_send, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

void RType::Client::start_receive()
{
    socket_.async_receive_from(
        boost::asio::buffer(recv_buffer_), server_endpoint_,
        boost::bind(&RType::Client::handle_receive, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

void RType::Client::handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error || error == boost::asio::error::message_size) {
        std::cout << "Received: " << std::string(recv_buffer_.data(), bytes_transferred) << std::endl;
        start_receive();
    } else {
        std::cerr << "Error receiving: " << error.message() << std::endl;
    }
}

void RType::Client::handle_send(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error) {
        std::cout << "Message sent." << std::endl;
    } else {
        std::cerr << "Error sending: " << error.message() << std::endl;
    }
}

void RType::Client::run_receive()
{
    io_context_.run();
}

void RType::Client::createSprite(const std::string& type, float x, float y)
{
    sf::Sprite sprite;
    SpriteType spriteType;

    if (type == "Enemy") {
        spriteType = SpriteType::Enemy;
    } else if (type == "Player") {
        spriteType = SpriteType::Player;
    } else if (type == "Missile") {
        spriteType = SpriteType::Missile;
    } else if (type == "Background") {
        spriteType = SpriteType::Background;
    } else {
        return;
    }

    sprite.setTexture(textures_[spriteType]);
    sprite.setPosition(x, y);
    sprites_.push_back(sprite);
}

void RType::Client::loadTextures()
{
    textures_[RType::SpriteType::Enemy].loadFromFile("enemy.png");
    textures_[RType::SpriteType::Player].loadFromFile("player.png");
    textures_[RType::SpriteType::Missile].loadFromFile("missile.png");
    textures_[RType::SpriteType::Background].loadFromFile("background.png");
}

void RType::Client::drawSprites(sf::RenderWindow& window)
{
    for (auto& sprite : sprites_) {
        window.draw(sprite);
    }
}

void RType::Client::updateSpritePosition(size_t index, float x, float y)
{
    if (index < sprites_.size()) {
        sprites_[index].setPosition(x, y);
    }
}

void RType::Client::parseMessage(const std::string& input)
{
    std::string type;
    std::string data;
    std::size_t index;
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

    createSprite(type, new_x, new_y);
    updateSpritePosition(index, new_x, new_y);
}

int RType::Client::main_loop()
{
    boost::asio::io_context io_context;
    RType::Client client(io_context, "localhost", 12345, 12346);

    client.loadTextures();

    sf::RenderWindow window(sf::VideoMode(800, 600), "R-Type Client");

    std::thread io_thread([&io_context]() {
        io_context.run();
    });

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        std::string input(client.recv_buffer_.data());
        client.parseMessage(input);

        window.clear();
        client.drawSprites(window);
        window.display();
    }

    io_context.stop();
    io_thread.join();

    return 0;
}
