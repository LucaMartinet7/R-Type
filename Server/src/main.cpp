/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** main
*/

#include <asio.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include "server.cpp"

int main() {
    try {
        asio::io_context io_context;

        Server server(io_context, "127.0.0.1", "8080", 1);

        std::thread io_thread([&io_context]() { io_context.run(); });

        io_thread.join();
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}