#include "objects.h"

PNU pnu("192.168.6.2", 10000, true, false);


void Init() {
    pnu.Reset();
    pnu.ReadReply();
    pnu.GetState();
    pnu.GetState();  // create pause for get state and other fast commands
    pnu.ReadReply();
    Transform::Cartesian cartesian_xyz = {1, 1, 1};  // init xyz0 coord
    auto pnu_angles = Transform::CartesianToPNU(cartesian_xyz);
    pnu.GoToPoint( pnu_angles.phi, pnu_angles.theta);
    pnu.ReadReply();
}

void Calculate() {
    Transform::Cartesian cartesian_xyz = {-1, 1, 2};  // xyz coord
    auto pnu_angles = Transform::CartesianToPNU(cartesian_xyz);
    pnu.GoToPoint(pnu_angles.phi, pnu_angles.theta);
}

void Stop() {
    pnu.ReadReply();
}



int main() {
    Init();
    Calculate();
    Stop();
    return 0;
}
