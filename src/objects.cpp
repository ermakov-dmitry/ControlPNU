#include "objects.h"

#define SEND(message) \
    message.n_packet = connecter_.GetPacketNumber();\
    std::vector<std::byte> send_data(sizeof(message));\
    memcpy(send_data.data(), &message, sizeof(message));\
    connecter_.SendMessage(send_data);\
    auto reply = connecter_.ReadMessage();\
    CheckReply(std::move(reply))\


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

void PNU::CheckReply(std::unique_ptr<const std::vector<std::byte>>&& reply) {
    try {
        reader_.UnpackReply(std::move(reply));
    } catch (std::invalid_argument& ex) {
        std::cerr << "Неизвестный код ответа\n";
        // error_file << unknown reply;
    } catch (std::domain_error&) {
        // GetState(); TODO problems with recursive
    }
}

void PNU::GetState() {
    Command message{};
    message.command = 0x0100;
    SEND(message);
}

void PNU::GoToPoint(long double azimuth, long double elevator) {
    MoveToPoint message{};
    message.azimuth = transformer_.DegToMkrad<uint16_t>(azimuth);
    message.elevator = transformer_.DegToMkrad<uint16_t>(elevator);
    SEND(message);
}

void PNU::SetMaxAccelerationAndSpeed(long double max_acc_azimuth, long double max_acc_elevator,
                                     long double max_spd_azimuth, long double max_spd_elevator) {
    SetMaxAccAndSpeed message{};
    message.max_accel_azimuth = transformer_.DegToMkrad<uint16_t>(max_acc_azimuth);
    message.max_accel_elevator = transformer_.DegToMkrad<uint16_t>(max_acc_elevator);
    message.max_velocity_azimuth = transformer_.DegToMkrad<uint16_t>(max_spd_azimuth);
    message.max_velocity_elevator = transformer_.DegToMkrad<uint16_t>(max_spd_elevator);
    SEND(message);
}

void PNU::Reset() {
    Command message{};
    message.command = 0x01F0;
    SEND(message);
    connecter_.ResetPackageNumber();
}


void Target::CreateLinearTrajectory(long double A, long double B, long double C, long double D, size_t count_points) {

}
