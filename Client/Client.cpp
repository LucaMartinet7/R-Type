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

void RType::Client::run() {
    send("REQCONNECT");
    while (window.isOpen()) {
        processEvents();
        render();
    }

    send("DISCONNECTED");
}

void RType::Client::createSprite(const std::string& type, int server_id, float x, float y)
{
    SpriteElement spriteElement;
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

    spriteElement.sprite.setTexture(textures_[spriteType]);
    spriteElement.sprite.setPosition(x, y);
    spriteElement.id = server_id;
    sprites_.push_back(spriteElement);
}

void RType::Client::destroySprite(size_t server_id)
{
    for (auto it = sprites_.begin(); it != sprites_.end(); ++it) {
        if (server_id == it->id) {
            sprites_.erase(it);
            break;
        }
    }
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
    for (auto& spriteElement : sprites_) {
        window.draw(spriteElement.sprite);
    }
}

void RType::Client::updateSpritePosition(size_t server_id, float x, float y)
{
    for (auto& spriteElement : sprites_) {
        if (server_id == spriteElement.id) {
            spriteElement.sprite.setPosition(x, y);
            break;
        }
    }
}

void RType::Client::parseMessage(const std::string& input) // parser that will be adjusted to the server's message
{
    std::string type; // these will be put in the class to be usable everywhere when a modification needs to be done to a sprite
    std::string data;
    std::size_t index;
    std::size_t server_id;
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

    createSprite(type, server_id, new_x, new_y);
    updateSpritePosition(index, new_x, new_y);
}

int RType::Client::main_loop()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "R-Type Client");
    loadTextures();

    while (window.isOpen()) {
        processEvents(window);

        std::string input(recv_buffer_.data());
        parseMessage(input);
        createSprite("Player", 0, 100, 100); //modify parameters to match the server's message that will be parsed
        destroySprite(0); //modify parameters to match the server's message that will be parsed
        updateSpritePosition(0, 100, 100); //modify parameters to match the server's message that will be parsed

        window.clear();
        drawSprites(window);
        window.display();
    }

    return 0;
}

void RType::Client::processEvents(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
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
            if (event.key.code == sf::Keyboard::Q) {
                window.close();
            }
            if (event.key.code == sf::Keyboard::M) {
                std::string message = "OPEN_MENU";
                send(message);
            }
        }
    }
}

