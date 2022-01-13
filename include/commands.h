#ifndef DIPLOMA_COMMANDS_H
#define DIPLOMA_COMMANDS_H
#include <cstdint>
#pragma once
#pragma pack(push, 1)

struct Command {  // read data, start/stop sequence
    uint16_t command{};
    uint16_t n_packet{};
};

struct MoveToPoint {
    const uint16_t command = 0x0101;
    uint16_t n_packet{};
    uint16_t azimuth{};
    uint16_t elevator{};
};

struct UploadPoint {
    const uint16_t command = 0x0102;
    uint16_t n_packet{};
    uint16_t n_point_move_load{};
    uint16_t azimuth{};
    uint16_t elevator{};
};

struct SetMaxAccAndSpeed {
    const uint16_t command = 0x0140;
    uint16_t n_packet{};
    uint16_t max_accel_azimuth{};
    uint16_t max_accel_elevator{};
    uint16_t max_velocity_azimuth{};
    uint16_t max_velocity_elevator{};
};

struct SetOffsetAndBoundsRotateAngles {
    const uint16_t command = 0x0120;
    uint16_t n_packet{};
    signed short offset_azimuth{};
    signed short offset_elevator{};
    uint16_t min_elevator{};
    uint16_t max_elevator{};
};

struct SetNewIP {
    const uint16_t command = 0x0F00;
    uint16_t n_packet{};
    unsigned char ip_adr[4]{};
    unsigned char copy_ip_adr[4]{};
};

struct SetNewUDPPort {
    const uint16_t command = 0x01FF;
    uint16_t n_packet{};
    uint16_t udp_port{};
    uint16_t copy_udp_port{};
};

#pragma pack(pop)

#endif //DIPLOMA_COMMANDS_H
