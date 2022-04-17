#ifndef DIPLOMA_OBJECTS_H
#define DIPLOMA_OBJECTS_H
#pragma once
#include <string>
#include <memory>
#include "connection.h"
#include "transformer.h"
#include "reader.h"
#include "commands.h"


class PNU {
public:
    explicit PNU(const std::string& ip_address, int port, bool is_print);  // may be other for new objects
    void GetState();
    void GoToPoint(double azimuth, double elevator);
    void SetMaxAccelerationAndSpeed(double max_acc_azimuth, double max_acc_elevator,
                                    double max_spd_azimuth, double max_spd_elevator);
    void Reset();
    void ReadReply();
    void ChangeIPAddress(const char* ip);
    ~PNU();
private:
    char* reply_pnu_;
    void CheckReply();
    UDPConnecter connecter_;
    Reader reader_;
};

extern PNU* pPNU;
void CreatePNU();
void InitPNU();
void CalculatePNU();
void StopPNU();


#endif //DIPLOMA_OBJECTS_H