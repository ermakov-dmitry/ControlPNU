#include "modes.h"

using namespace std;

Modes::Modes(PNU &pnu,
                           long double x,
                           long double y,
                           long double z) : pnu_(pnu), target_(x, y, z) {}

ModesBuilder& ModesBuilder::SetTargetXStart(long double x) {
    x_ = x;
    return *this;
}

ModesBuilder& ModesBuilder::SetTargetYStart(long double y) {
    y_ = y;
    return *this;
}

ModesBuilder& ModesBuilder::SetTargetZStart(long double z) {
    z_ = z;
    return *this;
}

Modes ModesBuilder::CreateModes(PNU &pnu) const {
    return Modes(pnu, x_, y_, z_);
}

void Modes::TargetLinearMotion() {
    long double Vx, Vy, Vz;
    int dt, time_end;
    cout << "Vx = ";
    cin >> Vx;
    cout << "Vy = ";
    cin >> Vy;
    cout << "Vz = ";
    cin >> Vz;
    /*cout << "ax = ";
    cin >> ax;
    cout << "ay = ";
    cin >> ay;
    cout << "az = ";
    cin >> az;*/
    cout << "dt (ms) = ";
    cin >> dt;
    cout << "t_end (sec) = ";
    cin >> time_end;
    time_end *= 1000;
    pnu_.Reset();
    pnu_.ReadReply();
    pnu_.GetState();
    pnu_.GetState();
    pnu_.ReadReply();
    auto spherical_target = Transform::CartesianToSpherical(target_.GetPosition());
    auto angles = Transform::SphericalToPNU(spherical_target);
    pnu_.GoToPoint(angles.get<0>(), angles.get<1>());
    pnu_.GetState();
    for (int t = 0; t <= time_end; t += dt) {
        spherical_target = Transform::CartesianToSpherical(target_.GetPosition());
        angles = Transform::SphericalToPNU(spherical_target);
        pnu_.GoToPoint(angles.get<0>(), angles.get<1>());
        auto dx = Vx * dt / 1000;
        auto dy = Vy * dt / 1000;
        auto dz = Vz * dt / 1000;
        target_.NextStepPosition(dx, dy, dz);
        std::this_thread::sleep_for(std::chrono::milliseconds(dt));
    }

}
