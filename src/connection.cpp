#include "connection.h"

using namespace std;

UDPConnecter::UDPConnecter(const std::string& ip_address, int port) {

    if ((socket_.sockfd = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&socket_.servaddr, 0, sizeof(socket_.servaddr));
    socket_.servaddr.sin_family = AF_INET;
    socket_.servaddr.sin_port = htons(port);
    socket_.servaddr.sin_addr.s_addr = inet_addr(ip_address.c_str());
    if (bind(socket_.sockfd,
  (const struct sockaddr *)&socket_.servaddr,
    sizeof(socket_.servaddr)) < 0 ) {
        throw runtime_error("bind failed");
    }
}

UDPConnecter::~UDPConnecter() {
    // sock_.close();
    close(socket_.sockfd);
}

void UDPConnecter::SendMessage(const std::vector<char>& data) {
    sendto(socket_.sockfd, data.data(), data.size(), 0,
           (const struct sockaddr *) &socket_.servaddr,sizeof(socket_.servaddr));
    packet_number_++;
}

std::unique_ptr<const std::vector<char>> UDPConnecter::ReadMessage() const {
    std::vector<char> data(1024);
    int addr_len;
    size_t n;
    do {
        n = recvfrom(socket_.sockfd, data.data(),
                     1024, 0, (sockaddr*)&socket_.servaddr,
                     (socklen_t*)(&addr_len));
    } while (n != 0);
    data.resize(n);
    data.shrink_to_fit();
    return std::make_unique<const std::vector<char>>(data);
}

uint16_t UDPConnecter::GetPacketNumber() const {
    return packet_number_;
}

void UDPConnecter::ResetPackageNumber() {
    packet_number_ = 1u;
}