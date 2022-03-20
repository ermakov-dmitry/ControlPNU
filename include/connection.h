#ifndef DIPLOMA_CONNECTION_H
#define DIPLOMA_CONNECTION_H
#pragma once
#include <string>
#include <cstring>
#include <iostream>
#include <memory>
#ifdef LOCAL_MACHINE
#include <cstdint>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#else
#include "sockLib.h"
#include "inetLib.h"
#endif
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

class PNU;

class UDPConnecter {
public:
    explicit UDPConnecter(const std::string& ip_address, int port, char* data);
    void SendMessage(char*);
    void ReadMessage() const;
    unsigned short GetPacketNumber() const;
    void ResetPackageNumber();
    ~UDPConnecter();
    friend PNU;
private:
    int port_;
    std::string ip_address_;
    unsigned short packet_number_;
    struct Socket {
        int sockfd;
        struct sockaddr_in servaddr;
    };
    void ChangeIP(const std::string& ip_address);
    char* reply_;
    Socket socket_;
};

#endif //DIPLOMA_CONNECTION_H
