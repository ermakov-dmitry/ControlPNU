#include "connection.h"

using namespace boost::asio;

UDPConnecter::UDPConnecter(std::string_view ip_address, int port)
    : resolver_(io_context_), sock_(io_context_), packet_number_(1u) {
    ep_ = *resolver_.resolve(ip::udp::v4(), ip_address, std::to_string(port)).begin();
    sock_.open(ip::udp::v4());
    sock_.connect(ep_);
}

UDPConnecter::~UDPConnecter() {
    sock_.close();
}

void UDPConnecter::SendMessage(void* data, size_t len) {
    sock_.send_to(buffer(data, len), ep_);
    packet_number_++;
}

std::unique_ptr<const std::vector<std::byte>> UDPConnecter::ReadMessage() {
    ip::udp::endpoint client;
    std::vector<std::byte> data;
    data.reserve(1024);
    bool wait_first_message = true;
    while (sock_.available() > 0 || wait_first_message) {
        wait_first_message = false;
        sock_.receive_from(buffer(data), client);
    }
    data.shrink_to_fit();
    return std::make_unique<const std::vector<std::byte>>(data);
}

uint16_t UDPConnecter::GetPacketNumber() const {
    return packet_number_;
}

void UDPConnecter::ResetPackageNumber() {
    packet_number_ = 1u;
}