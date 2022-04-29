#ifndef DIPLOMA_OBJECTS_H
#define DIPLOMA_OBJECTS_H
#pragma once
#include <string>
#include <memory>
#include "connection.h"
#include "transformer.h"
#include "reader.h"
#include "commands.h"
#ifndef LOCAL_MACHINE
#include "globaldefs.h"
#include "ModelEnable.h"
#endif

struct Offsets {
    double azimuth;
    double elevator;
};

struct Bounds {
    double min_azimuth;
    double max_azimuth;
    double min_elevator;
    double max_elevator;
};

struct MaxSpeedData {
    double azimuth_acceleration;
    double elevator_acceleration;
    double azimuth_velocity;
    double elevator_velocity;
};

class PNU {
public:
    explicit PNU(const std::string& ip_address, int port);  // may be other for new objects
    void GetState();
    void GoToPoint(double azimuth, double elevator);
    void SetMaxAccelerationAndSpeed(const MaxSpeedData&);
    void Reset();
    void ReadReply();
    void ChangeIPAddress(const char* ip);

#ifndef LOCAL_MACHINE
    void npsk_ssk(double &x, double &y, double &z);
#endif
    void SetOffsetsAndBounds(Offsets offsets, const Bounds& bounds);
    void GetOutput();
    ~PNU();
    struct Setup {
        int manual_mode;
        int ust;
        int cartesizan_mode;
        double x;
        double y;
        double z;
        double azimuth;
        double elevator;
        double azimuth_offset;
        double elevator_offset;
        double min_elevator;
        double max_elevator;
        double lb_azimuth;
        double rb_azimuth;
    };
    struct Output{
        double azimuth;
        double elevator;
    };
    Setup setup_;
    Output output_;
    bool is_init_;
private:
    char* reply_pnu_;
    void CheckReply();
    UDPConnecter connecter_;
    Reader reader_;
    double azimuth_offset_;
    double elevator_offset_;
    double azimuth_;
    double elevator_;
};

#ifndef LOCAL_MACHINE
extern PNU* pPNU;
void CreatePNU();
void InitPNU();
void CalculatePNU();
void StopPNU();
#endif


#endif //DIPLOMA_OBJECTS_H
