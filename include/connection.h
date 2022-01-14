#ifndef DIPLOMA_CONNECTION_H
#define DIPLOMA_CONNECTION_H
#pragma once
#include <string_view>
#include <iostream>
#include <memory>
#include <cstdint>
#include <boost/asio.hpp>
#include "logger.h"

class UDPConnecter {
public:
    explicit UDPConnecter(std::string_view ip_address, int port);
    void SendMessage(const std::vector<std::byte>&);
    std::unique_ptr<const std::vector<std::byte>> ReadMessage();
    [[nodiscard]] uint16_t GetPacketNumber() const;
    void ResetPackageNumber();
    ~UDPConnecter();

private:
    boost::asio::io_context io_context_;
    boost::asio::ip::udp::resolver resolver_;
    boost::asio::ip::udp::endpoint ep_;
    boost::asio::ip::udp::socket sock_;
    uint16_t packet_number_;
};

#endif //DIPLOMA_CONNECTION_H
