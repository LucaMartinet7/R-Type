/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** server
*/

#include <asio.hpp>
#include <iostream>
#include <thread>
#include <vector>

class Server {
    public:
        Server(asio::io_context& io_context, const std::string& host, const std::string& port, int num_threads)
            : acceptor_(io_context, asio::ip::tcp::endpoint(asio::ip::make_address(host), std::stoi(port))) {
            for (int i = 0; i < num_threads; i++) {
                threads_.emplace_back([&io_context]() { io_context.run(); });
            }
            do_accept();
        }

        ~Server() {
            for (auto& thread : threads_) {
                thread.join();
            }
        }

        void do_accept() {
            acceptor_.async_accept(
                [this](std::error_code ec, asio::ip::tcp::socket socket) {
                    if (!ec) {
                        std::cout << "New connection from " << socket.remote_endpoint().address().to_string() << "\n";
                    }
                    do_accept();
                });
    }
    private:
    asio::ip::tcp::acceptor acceptor_;
    std::vector<std::thread> threads_;
};

