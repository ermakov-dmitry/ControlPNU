#include "objects.h"

#define SEND(message) \
    message.n_packet = connecter_.GetPacketNumber();\
    std::vector<char> send_data(sizeof(message));\
    memcpy(send_data.data(), &message, sizeof(message));\
    connecter_.SendMessage(send_data);\
    //auto reply = connecter_.ReadMessage();\
    //CheckReply(std::move(reply))\


PNU::PNU(const std::string& ip_address,
         int port, bool is_print,
         bool is_log) : connecter_(ip_address, port),
         reader_(is_print, is_log) {}

void PNU::CheckReply(std::vector<char>&& reply) {
    try {
        reader_.UnpackReply(std::move(reply));
    } catch (std::invalid_argument& ex) {
        std::cerr << ex.what();
        throw;
        // error_file << unknown reply;
    } // catch (std::domain_error&) {
        // GetState();  // TODO problems with recursive
    // }
}

void PNU::GetState() {
    Command message{};
    message.command = 0x0100;
    SEND(message);
}

void PNU::GoToPoint(long double azimuth, long double elevator) {
    MoveToPoint message{};
    message.azimuth = Transform::DegToMkrad<uint16_t>(azimuth);
    message.elevator = Transform::DegToMkrad<uint16_t>(elevator);
    SEND(message);
}

void PNU::SetMaxAccelerationAndSpeed(long double max_acc_azimuth, long double max_acc_elevator,
                                     long double max_spd_azimuth, long double max_spd_elevator) {
    SetMaxAccAndSpeed message{};
    message.max_accel_azimuth = Transform::DegToMkrad<uint16_t>(max_acc_azimuth);
    message.max_accel_elevator = Transform::DegToMkrad<uint16_t>(max_acc_elevator);
    message.max_velocity_azimuth = Transform::DegToMkrad<uint16_t>(max_spd_azimuth);
    message.max_velocity_elevator = Transform::DegToMkrad<uint16_t>(max_spd_elevator);
    SEND(message);
}

void PNU::Reset() {
    Command message{};
    message.command = 0x01F0;
    SEND(message);
    connecter_.ResetPackageNumber();
}

void PNU::ReadReply() {
    CheckReply(std::move(connecter_.ReadMessage()));
}
