#include "scenarios.h"

using namespace std;

Screenwriter::Screenwriter(PNU &pnu,
                           long double x,
                           long double y,
                           long double z) : pnu_(pnu), target_(x, y, z) {}

ScreenwriterBuilder& ScreenwriterBuilder::SetTargetXStart(long double x) {
    x_ = x;
    return *this;
}

ScreenwriterBuilder& ScreenwriterBuilder::SetTargetYStart(long double y) {
    y_ = y;
    return *this;
}

ScreenwriterBuilder& ScreenwriterBuilder::SetTargetZStart(long double z) {
    z_ = z;
    return *this;
}

Screenwriter ScreenwriterBuilder::CreateScreenwriter(PNU &pnu) {
    return Screenwriter(pnu, x_, y_, z_);
}

void Screenwriter::TargetLinearMotion() {
    long double Vx, Vy, Vz, ax, ay, az, dt;
    cout << "Vx = ";
    cin >> Vx;
    cout << "Vy = ";
    cin >> Vy;
    cout << "Vz = ";
    cin >> Vz;
    cout << "ax = ";
    cin >> ax;
    cout << "ay = ";
    cin >> ay;
    cout << "az = ";
    cin >> az;
    cout << "dt = ";
    cin >> dt;

}
