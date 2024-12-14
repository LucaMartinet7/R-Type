/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** main
*/

#include "Client.hpp"

int main(int ac, char **av)
{
    if (ac != 3) {
        std::cerr << "Usage: " << av[0] << " <host> <port>" << std::endl;
        return 1;
    }

    std::string host = av[1];
    short port = std::stoi(av[2]);

    try {
        boost::asio::io_context io_context;
        RType::Client client(io_context, host, port);

        std::string message;
        while (std::getline(std::cin, message)) {
            client.send(message);
        }

        io_context.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}