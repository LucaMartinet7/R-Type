/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu]
** File description:
** Throws
*/

#pragma once

#include <exception>
#include <string>

#define NEW_EXCEPTION(name)                                                        \
    class name : public RType::NtsException                                        \
    {                                                                              \
    public:                                                                        \
        name(std::string const &message, std::string const &type = #name) noexcept \
            : RType::NtsException(message, type) {}                                \
    };

namespace RType
{
    class NtsException : public std::exception
    {
    public:
        NtsException(std::string const &message, std::string const &type = "Unknown") noexcept
        {
            _message = message;
            _type = type;
        }

        std::string const &getType() const { return _type; }
        const char *what() const noexcept override { return _message.c_str(); }

    private:
        std::string _message;
        std::string _type;
    };

    //parse
    NEW_EXCEPTION(InvalidPortException)
    //general
    NEW_EXCEPTION(StandardException)
    NEW_EXCEPTION(UnknownException)
}