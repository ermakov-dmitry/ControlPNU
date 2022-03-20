#ifndef DIPLOMA_COMMANDS_H
#define DIPLOMA_COMMANDS_H
#include <cstdint>
#pragma once
#pragma pack(push, 1)

struct Command {  // read data, start/stop sequence
    unsigned short command;
    unsigned short n_packet;
};

struct MoveToPoint {
    unsigned short command;
    unsigned short n_packet;
    unsigned short azimuth;
    unsigned short elevator;
};

struct UploadPoint {
    unsigned short command;
    unsigned short n_packet;
    unsigned short n_point_move_load;
    unsigned short azimuth;
    unsigned short elevator;
};

struct SetMaxAccAndSpeed {
    unsigned short command;
    unsigned short n_packet;
    unsigned short max_accel_azimuth;
    unsigned short max_accel_elevator;
    unsigned short max_velocity_azimuth;
    unsigned short max_velocity_elevator;
};

struct SetOffsetAndBoundsRotateAngles {
    unsigned short command;
    unsigned short n_packet;
    signed short offset_azimuth;
    signed short offset_elevator;
    unsigned short min_elevator;
    unsigned short max_elevator;
};

struct SetNewIP {
    unsigned short command;
    unsigned short n_packet;
    unsigned char ip_adr[4];
    unsigned char copy_ip_adr[4];
};

struct SetNewUDPPort {
    unsigned short command;
    unsigned short n_packet;
    unsigned short udp_port;
    unsigned short copy_udp_port;
};

#pragma pack(pop)

#endif //DIPLOMA_COMMANDS_H
