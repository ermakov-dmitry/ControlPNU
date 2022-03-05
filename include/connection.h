#ifndef DIPLOMA_CONNECTION_H
#define DIPLOMA_CONNECTION_H
#pragma once
#include <string>
#include <cstring>
#include <iostream>
#include <memory>
#include <cstdint>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "logger.h"

class UDPConnecter {
public:
    explicit UDPConnecter(const std::string& ip_address, int port);
    void SendMessage(const std::vector<char>&);
    [[nodiscard]] std::unique_ptr<const std::vector<char>> ReadMessage() const;
    [[nodiscard]] uint16_t GetPacketNumber() const;
    void ResetPackageNumber();
    ~UDPConnecter();

private:
    struct Socket {
        int sockfd{};
        struct sockaddr_in servaddr{};
    };
    Socket socket_;
    uint16_t packet_number_ = 0;
};

#endif //DIPLOMA_CONNECTION_H
