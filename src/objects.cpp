#include "objects.h"

PNUCreator &PNUCreator::SetIPAddress(std::string_view ip_address) {
    ip_address_ = ip_address;
    return *this;
}

PNUCreator &PNUCreator::SetPort(int port) {
    port_ = port;
    return *this;
}

PNUCreator &PNUCreator::PrintReplies(bool flag) {
    is_print = flag;
    return *this;
}

PNUCreator &PNUCreator::LogReplies(bool flag) {
    is_log = flag;
    return *this;
}

PNU PNUCreator::CreatePNU() {
    return PNU(ip_address_, port_, is_print, is_log);
}

PNU::PNU(std::string_view ip_address,
         int port, bool is_print,
         bool is_log) : connecter_(ip_address, port),
         reader_(is_print, is_log) {}

void PNU::GetState() const {
    Command get_state{};  // TODO need remake to classes
    get_state.command = 0x0100;
    get_state.n_packet = connecter_.GetPacketNumber();
    connecter_.SendMessage(&get_state, sizeof(get_state));
    auto reply = connecter_.ReadMessage();
    try {
        reader_.DefineReply(move(reply));
    } catch (std::invalid_argument& ex) {
        // parse error code
    }
}

// logger