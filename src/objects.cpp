#include "objects.h"

PNU *pPNU = NULL;

PNU::PNU(const std::string& ip_address, int port, bool is_print) :
        reply_pnu_(new char[1024]), connecter_(ip_address, port, reply_pnu_), reader_(
        is_print, reply_pnu_) {}

PNU::~PNU() {
  delete[] reply_pnu_;
}

void PNU::CheckReply() {
  reader_.UnpackReply();
}

void PNU::GetState() {
  Command message;
  message.command = 0x0100;
  message.n_packet = connecter_.GetPacketNumber();
  char* send_data = new char[sizeof(message)];
  memcpy(send_data, &message, sizeof(message));
  connecter_.SendMessage(send_data);
  delete[] send_data;
}

void PNU::GoToPoint(double azimuth, double elevator) {
  MoveToPoint message;
  message.command = 0x0101;
  message.azimuth = Transform::DegToMkrad<unsigned short>(azimuth);
  message.elevator = Transform::DegToMkrad<unsigned short>(elevator);
  message.n_packet = connecter_.GetPacketNumber();
  char* send_data = new char[sizeof(message)];
  memcpy(send_data, &message, sizeof(message));
  connecter_.SendMessage(send_data);
  delete[] send_data;
}

void PNU::SetMaxAccelerationAndSpeed(double max_acc_azimuth,
                                     double max_acc_elevator, double max_spd_azimuth,
                                     double max_spd_elevator) {
  SetMaxAccAndSpeed message;
  message.command = 0x0140;
  message.max_accel_azimuth
          = Transform::DegToMkrad<unsigned short>(max_acc_azimuth);
  message.max_accel_elevator = Transform::DegToMkrad<unsigned short>(
          max_acc_elevator);
  message.max_velocity_azimuth = Transform::DegToMkrad<unsigned short>(
          max_spd_azimuth);
  message.max_velocity_elevator = Transform::DegToMkrad<unsigned short>(
          max_spd_elevator);
  message.n_packet = connecter_.GetPacketNumber();
  char* send_data = new char[sizeof(message)];
  memcpy(send_data, &message, sizeof(message));
  connecter_.SendMessage(send_data);
  delete[] send_data;
}

void PNU::Reset() {
  Command message;
  message.command = 0x01F0;
  message.n_packet = connecter_.GetPacketNumber();
  char* send_data = new char[sizeof(message)];
  memcpy(send_data, &message, sizeof(message));
  connecter_.SendMessage(send_data);
  connecter_.ResetPackageNumber();
  delete[] send_data;
}

void PNU::ReadReply() {
  connecter_.ReadMessage();
  CheckReply();
}

void CreatePNU() {
  if (pPNU == NULL)
    pPNU = new PNU("192.168.6.2", 10000, false);
}

void InitPNU() {
  if (pPNU) {
    pPNU->Reset();
    pPNU->ReadReply();
    pPNU->GetState();
    pPNU->GetState();
    pPNU->ReadReply();
    Transform::Cartesian cartesian_xyz = { 0, 0, 0 }; // xyz coord
    Transform::Spherical pnu_angles = Transform::CartesianToPNU(cartesian_xyz);
    pPNU->GoToPoint(pnu_angles.phi, pnu_angles.theta);
  }
}

void CalculatePNU() {
  if (pPNU) {
    Transform::Cartesian cartesian_xyz = { 0, 0, 0 }; // xyz coord
    Transform::Spherical pnu_angles = Transform::CartesianToPNU(cartesian_xyz);
    pPNU->GoToPoint(pnu_angles.phi, pnu_angles.theta);
  }
}

void StopPNU() {
  if (pPNU)
    pPNU->ReadReply();
}