#include "objects.h"

std::unique_ptr<PNU> pnu;

void Init() {
    PNUCreator creator;
    creator.SetIPAddress("192.168.6.2").SetPort(10'000)
    .PrintReplies(true).LogReplies(false);
    std::unique_ptr<PNU> pnu_local = creator.CreatePNU();
    pnu.swap(pnu_local);
    pnu->Reset();
    pnu->ReadReply();
    pnu->GetState();
    pnu->GetState();  // create pause for get state and other fast commands
    pnu->ReadReply();
    Transform::Cartesian cartesian_xyz = {1, 1, 1};  // init xyz0 coord
    auto pnu_angles = Transform::CartesianToPNU(cartesian_xyz);
    pnu->GoToPoint( pnu_angles.phi, pnu_angles.theta);
    pnu->ReadReply();
}

void Calculate() {
    Transform::Cartesian cartesian_xyz = {-1, 1, 2};  // xyz coord
    auto pnu_angles = Transform::CartesianToPNU(cartesian_xyz);
    pnu->GoToPoint(pnu_angles.phi, pnu_angles.theta);
}

void Stop() {
    pnu->ReadReply();
}



int main() {
    Init();
    Calculate();
    Stop();
    return 0;
}
