#include "connection.h"

using namespace std;

UDPConnecter::UDPConnecter(const std::string& ip_address, int port, char* data) {

  if ((socket_.sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }
  memset(&socket_.servaddr, 0, sizeof(socket_.servaddr));
  socket_.servaddr.sin_family = AF_INET;
  socket_.servaddr.sin_port = htons(port);
  socket_.servaddr.sin_addr.s_addr = inet_addr(ip_address.c_str());
  reply_ = data;
  packet_number_ = 1;
}

UDPConnecter::~UDPConnecter() {
  close(socket_.sockfd);
}

void UDPConnecter::SendMessage(char* data) {
  sendto(socket_.sockfd, data, sizeof(data), 0,
         (sockaddr *) &socket_.servaddr,sizeof(socket_.servaddr));
  packet_number_++;
}

void UDPConnecter::ReadMessage() const {
  bool is_wait = true;
  ssize_t bytes_read;
  int flag = MSG_WAITALL;
  do {
    bytes_read = recv(socket_.sockfd, reply_, 1024, flag);
    if (bytes_read > 0) {
      is_wait = false;
      flag = MSG_DONTWAIT;
    }
  } while (bytes_read > 0 || is_wait);
}

unsigned short UDPConnecter::GetPacketNumber() const {
  return packet_number_;
}

void UDPConnecter::ResetPackageNumber() {
  packet_number_ = 1;
}