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
    // operator=(const PNU&) = delete;
    void GetState();
    void GoToPoint(long double azimuth, long double elevator);
    void SetMaxAccelerationAndSpeed(long double max_acc_azimuth, long double max_acc_elevator,
                                    long double max_spd_azimuth, long double max_spd_elevator);
    void Reset();
private:
    explicit PNU(std::string_view ip_address, int port, bool is_print, bool is_log);  // may be other for new objects
    void CheckReply(std::unique_ptr<const std::vector<std::byte>>&&);
    Transformer transformer_;
    mutable UDPConnecter connecter_;
    Reader reader_;
};

class PNUCreator {
public:
    PNUCreator() = default;
    PNUCreator& SetIPAddress(std::string_view ip_address);
    PNUCreator& SetPort(int port);
    PNUCreator& PrintReplies(bool flag);
    PNUCreator& LogReplies(bool flag);
    PNU CreatePNU();
private:
    std::string ip_address_ = "127.0.0.1";
    int port_ = 10'000;
    bool is_print = false;
    bool is_log = false;
};

class Target {
public:
    explicit Target(long double x, long double y, long double z);
    void SetPosition(long double x, long double y, long double z);
    void NextStepPosition(long double dx, long double dy, long double dz);
    [[nodiscard]] boost::geometry::model::point<long double,
    3, boost::geometry::cs::cartesian> GetPosition() const;
private:
    boost::geometry::model::point<long double, 3, boost::geometry::cs::cartesian> position_;
};

// TODO may be change to namespace Trajectories

#endif //DIPLOMA_OBJECTS_H
