#include "objects.h"

#ifndef LOCAL_MACHINE
PNU *pPNU = nullptr;
#endif

PNU::PNU(const std::string& ip_address, int port) :
        setup_(), output_(), is_init_(false),
        reply_pnu_(new char[1024]), connecter_(ip_address, port, reply_pnu_),
        reader_(reply_pnu_), azimuth_offset_(0), elevator_offset_(0), azimuth_(0), elevator_(0)  {
    setup_.manual_mode = 1;
    setup_.ust = 1;
    setup_.cartesizan_mode = 1;
    setup_.x = 1;
    setup_.y = 0;
    setup_.z = 0;
    setup_.azimuth = azimuth_;
    setup_.elevator = elevator_;
    setup_.azimuth_offset = azimuth_offset_;
    setup_.elevator_offset = elevator_offset_;
    setup_.min_elevator = -45;
    setup_.max_elevator = 45;
    setup_.min_azimuth = 80;
    setup_.max_azimuth = -80;
}

PNU::~PNU() {
    delete[] reply_pnu_;
}

void PNU::CheckReply() {
    Position pos;
    pos = reader_.UnpackReply();
    if (pos.azimuth != -1 && pos.elevator != -1) {
        azimuth_ = pos.azimuth;
        elevator_ = pos.elevator - 180;
    }
}

void PNU::GetState() {
    Command message;
    message.command = 0x0100;
    message.n_packet = connecter_.GetPacketNumber();
    connecter_.SendData((char*) &message, 4);
}

void PNU::GoToPoint(double azimuth, double elevator) {
    // TODO: Add offsets
    Transform::Spherical pos = {1, elevator + elevator_offset_ + 180, azimuth + azimuth_offset_};
    pos = Transform::ReduceAngles(pos);
    MoveToPoint message;
    message.command = 0x0101;
    message.azimuth = Transform::DegToMkrad<unsigned short>(pos.phi);
    message.elevator = Transform::DegToMkrad<unsigned short>(pos.theta);
    message.n_packet = connecter_.GetPacketNumber();
    connecter_.SendData((char*) &message, 8);
}

void PNU::SetMaxAccelerationAndSpeed(const MaxSpeedData& values) {
    SetMaxAccAndSpeed message;
    message.command = 0x0140;
    message.max_accel_azimuth     = Transform::DegToMkrad<unsigned short>(values.azimuth_acceleration);
    message.max_accel_elevator    = Transform::DegToMkrad<unsigned short>(values.elevator_acceleration);
    message.max_velocity_azimuth  = Transform::DegToMkrad<unsigned short>(values.azimuth_velocity);
    message.max_velocity_elevator = Transform::DegToMkrad<unsigned short>(values.elevator_velocity);
    message.n_packet = connecter_.GetPacketNumber();
    connecter_.SendData((char*) &message, 12);
}

void PNU::Reset() {
    Command message;
    message.command = 0x01F0;
    message.n_packet = connecter_.GetPacketNumber();
    connecter_.SendData((char*) &message, 4);
    connecter_.ResetPackageNumber();
}

void PNU::ReadReply() {
    connecter_.ReadData();
    CheckReply();
}

void PNU::ChangeIPAddress(const char* ip) {
    SetNewIP message;
    message.command = 0x0F00;
    sscanf(ip, "%d.%d.%d.%d", &message.ip_adr[0], &message.ip_adr[1],
           &message.ip_adr[2], &message.ip_adr[3]);
    for (size_t i = 0; i < 4; i++) {
        message.copy_ip_adr[i] = message.ip_adr[i];
    }
    message.n_packet = connecter_.GetPacketNumber();
    connecter_.SendData((char*) &message, 12);
    ReadReply();
    connecter_.ChangeIP(std::string(ip));
}

void PNU::SetOffsetsAndBounds(Offsets offsets, const Bounds &bounds) {
    azimuth_offset_ = offsets.azimuth;
    elevator_offset_ = offsets.elevator;
    // TODO: test with offset vars and command
    SetOffsetAndBoundsRotateAngles message;
    message.command = 0x0120;
    message.n_packet = connecter_.GetPacketNumber();
    message.offset_azimuth = 0;
    message.offset_elevator = 0;
    message.min_elevator = Transform::DegToMkrad<unsigned short>(bounds.min_elevator + 180);
    message.max_elevator = Transform::DegToMkrad<unsigned short>(bounds.max_elevator + 180);
    setup_.min_azimuth = bounds.min_azimuth;
    setup_.max_azimuth = bounds.max_azimuth;
    connecter_.SendData((char*) &message, 12);
}

void PNU::GetOutput() {
    output_.azimuth = azimuth_;
    output_.elevator = elevator_;
}

#ifndef LOCAL_MACHINE
void PNU::npsk_ssk(double &_x, double &_y, double &_z) {
    double x, y, z;

    // ������� ��������� ��������:
    double psi = -WorkElementBuffer->Kinematiks_aircraft.psic_aircraft
                 * GRAD2RAD;
    double teta = WorkElementBuffer->Kinematiks_aircraft.tetac_aircraft
                  * GRAD2RAD;
    double gama = WorkElementBuffer->Kinematiks_aircraft.gamac_aircraft
                  * GRAD2RAD;

    // ����������� ������� ������� ��������� � ���������
    // ����������� ���� ��������.
    // ��� ������ ������� �� �������� �� �������� ������ :)
    double cos_teta = cos(teta);
    double sin_teta = sin(teta);
    double cos_psi = cos(psi);
    double sin_psi = sin(psi);
    double cos_gama = cos(gama);
    double sin_gama = sin(gama);

    // ������������� ��������� ����� ���������.
    // ���������� ���� - ���������� �������� ��� �������� ������� �����
    x = WorkElementBuffer->DesTarget[0].x_target
        - WorkElementBuffer->Kinematiks_aircraft.xc_aircraft;
    y = WorkElementBuffer->DesTarget[0].y_target
        - WorkElementBuffer->Kinematiks_aircraft.yc_aircraft;
    z = WorkElementBuffer->DesTarget[0].z_target
        - WorkElementBuffer->Kinematiks_aircraft.zc_aircraft;

    // ��������� ���� � ���.
    double Ox_c = x * (cos_teta * cos_psi) + y * (sin_teta) + z * (-cos_teta * sin_psi);
    double Oy_c = x * (-cos_gama * sin_teta * cos_psi + sin_gama * sin_psi)
            + y * (cos_gama * cos_teta) + z * (sin_psi * sin_teta * cos_gama + sin_gama * cos_psi);
    double Oz_c = x * (sin_gama * sin_teta * cos_psi + cos_gama * sin_psi)
            - y * (sin_gama * cos_teta) + z * (-sin_gama * sin_teta * sin_psi + cos_gama * cos_psi);

    _x = Ox_c;
    _y = Oy_c;
    _z = Oz_c;
}

void CreatePNU() {
    if (pPNU == NULL)
        pPNU = new PNU("192.168.59.218", 10000);
}

void InitPNU() {
    if (pPNU) {
        pPNU->Reset();
        pPNU->ReadReply();
        pPNU->GetState();
        pPNU->GetState();
        pPNU->ReadReply();
        Offsets offsets;
        offsets.azimuth = 0;
        offsets.elevator = 0;
        Bounds bounds;
        bounds.min_azimuth = -80;
        bounds.max_azimuth = 80;
        bounds.min_elevator = -45;
        bounds.max_elevator = 45;
        pPNU->SetOffsetsAndBounds(offsets, bounds);
        pPNU->ReadReply();
        if (!pPNU->setup_.manual_mode) {
            if (NUMBER_TARGET > 0) {
                double x_target, y_target, z_target;
                pPNU->npsk_ssk(x_target, y_target, z_target);
                Transform::Cartesian cartesian_xyz = {x_target, y_target, z_target}; // xyz coord
                Transform::Spherical pnu_angles = Transform::CartesianToPNU(cartesian_xyz);
                pPNU->GoToPoint(pnu_angles.phi, pnu_angles.theta);
            }
        } else {
            if (pPNU->setup_.cartesizan_mode) {
                Transform::Cartesian cartesian_xyz = { pPNU->setup_.x, pPNU->setup_.y, pPNU->setup_.z }; // xyz coord
                Transform::Spherical pnu_angles = Transform::CartesianToPNU(cartesian_xyz);
                pPNU->GoToPoint(pnu_angles.phi, pnu_angles.theta);
            } else {
                pPNU->GoToPoint(pPNU->setup_.azimuth,  pPNU->setup_.elevator);
            }
        }
    }
}

void CalculatePNU()
{
    if (pPNU) {
        if(modelEnable.PNU) {
            if (!pPNU->is_init_) {
                pPNU->is_init_ = true;
                InitPNU();
            }
            if (!pPNU->setup_.manual_mode) {
                if (NUMBER_TARGET > 0) {
                    double x_target, y_target, z_target;
                    pPNU->npsk_ssk(x_target, y_target, z_target);
                    Transform::Cartesian cartesian_xyz = { x_target, y_target,z_target }; // xyz coord
                    Transform::Spherical pnu_angles = Transform::CartesianToPNU(cartesian_xyz);
                    pPNU->GoToPoint(pnu_angles.phi, pnu_angles.theta);
                }
            } else {
                if (pPNU->setup_.cartesizan_mode) {
                    Transform::Cartesian cartesian_xyz = { pPNU->setup_.x, pPNU->setup_.y, pPNU->setup_.z }; // xyz coord
                    Transform::Spherical pnu_angles = Transform::CartesianToPNU(cartesian_xyz);
                    pPNU->GoToPoint(pnu_angles.phi, pnu_angles.theta);
                } else {
                    pPNU->GoToPoint(pPNU->setup_.azimuth,  pPNU->setup_.elevator);
                }
                if (pPNU->setup_.ust) {
                    Offsets offsets;
                    offsets.azimuth = setup_.azimuth_offset;
                    offsets.elevator = setup_.elevator_offset;
                    Bounds bounds;
                    bounds.min_azimuth = setup_.min_azimuth;
                    bounds.max_azimuth = setup_.max_azimuth;
                    bounds.min_elevator = setup_.min_elevator;
                    bounds.max_elevator = setup_.max_elevator;
                    pPNU->SetOffsetsAndBounds(offsets, bounds);
                    pPNU->setup_.ust = false;
                }
            }
            pPNU->GetOutput();
        } else {
            pPNU->is_init_ = false;
        }
    }
}

void StopPNU() {
    if (pPNU) {
        pPNU->ReadReply();
    }
}
#endif
