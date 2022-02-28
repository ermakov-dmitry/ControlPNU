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
    struct Socket {
        int sockfd{};
        struct sockaddr_in servaddr{};
    };
    explicit UDPConnecter(const std::string& ip_address, int port);
    void SendMessage(const std::vector<std::byte>&);
    std::unique_ptr<const std::vector<std::byte>> ReadMessage();
    [[nodiscard]] uint16_t GetPacketNumber() const;
    void ResetPackageNumber();
    ~UDPConnecter();

private:
    Socket socket_;
    uint16_t packet_number_;
};

#endif //DIPLOMA_CONNECTION_H
