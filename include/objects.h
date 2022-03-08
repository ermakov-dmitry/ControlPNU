#ifndef DIPLOMA_OBJECTS_H
#define DIPLOMA_OBJECTS_H
#pragma once
#include <string>
#include <memory>
#include "connection.h"
#include "transformer.h"
#include "logger.h"
#include "reader.h"
#include "commands.h"

class PNUCreator;

class PNU {
public:
    friend PNUCreator;
    PNU (const PNU&) = delete;
    PNU& operator=(const PNU&) = delete;
    PNU (PNU&&) = delete;
    PNU& operator=(PNU&&) = delete;
    explicit PNU(const std::string& ip_address, int port, bool is_print, bool is_log);  // may be other for new objects
    void GetState();
    void GoToPoint(long double azimuth, long double elevator);
    void SetMaxAccelerationAndSpeed(long double max_acc_azimuth, long double max_acc_elevator,
                                    long double max_spd_azimuth, long double max_spd_elevator);
    void Reset();
    void ReadReply();
private:
    void CheckReply(std::vector<char>&&);
    UDPConnecter connecter_;
    Reader reader_;
};



#endif //DIPLOMA_OBJECTS_H
