#include "connection.h"

using namespace std;

UDPConnecter::UDPConnecter(const std::string& ip_address, int port) {

    if ((socket_.sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&socket_.servaddr, 0, sizeof(socket_.servaddr));
    socket_.servaddr.sin_family = AF_INET;
    socket_.servaddr.sin_port = htons(port);
    socket_.servaddr.sin_addr.s_addr = inet_addr(ip_address.data());
    socket_.sockfd = fcntl(socket_.sockfd, int cmd)
}

UDPConnecter::~UDPConnecter() {
    // sock_.close();
    close(socket_.sockfd);
}

void UDPConnecter::SendMessage(const std::vector<std::byte>& data) {
    sendto(socket_.sockfd, data.data(), data.size(), 0,
           (const struct sockaddr *) &socket_.servaddr,sizeof(socket_.servaddr));
    packet_number_++;
}

std::unique_ptr<const std::vector<std::byte>> UDPConnecter::ReadMessage() {
    std::vector<std::byte> data(1024);
    bool wait_first_message = true;
    unsigned long len = 0;
    /*while (sock_.available() > 0 || wait_first_message) {
        wait_first_message = false;
        len = sock_.receive_from(buffer(data), client);
    }*/ // read full quque
  int bytesRead = 0;
  int result;
  while (bytesRead < x) {
    result = read(socket, data.data() + bytesRead, x - bytesRead);
    if (result < 1 )
    {
      // Throw your error.
    }

    bytesRead += result;
  }
    data.resize(len);
    data.shrink_to_fit();
    return std::make_unique<const std::vector<std::byte>>(data);
}

uint16_t UDPConnecter::GetPacketNumber() const {
    return packet_number_;
}

void UDPConnecter::ResetPackageNumber() {
    packet_number_ = 1u;
}