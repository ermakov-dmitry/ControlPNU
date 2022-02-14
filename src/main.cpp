#include "objects.h"

std::unique_ptr<PNU> pnu;

void Init() {
    PNUCreator creator;
    creator.SetIPAddress("192.168.6.2")
            .SetPort(10'000)
            .PrintReplies(true)
            .LogReplies(true);
    std::unique_ptr<PNU> pnu_local = creator.CreatePNU();
    pnu.swap(pnu_local);
    pnu->Reset();
    pnu->ReadReply();
    pnu->GetState();
    pnu->GetState();
    pnu->ReadReply();
    auto cartesian_xyz = Transform::AviaToCartesian({1, 2, 3});  // xyz coord
    auto spherical = Transform::CartesianToSpherical(cartesian_xyz);
    auto pnu_theta_phi = Transform::SphericalToPNU(spherical);
    pnu->GoToPoint(pnu_theta_phi.get<0>(), pnu_theta_phi.get<1>());
    pnu->GetState();
}

void Calculate() {
    pnu->ReadReply();
    auto cartesian_xyz = Transform::AviaToCartesian({1, 2, 3});  // xyz coord
    auto spherical = Transform::CartesianToSpherical(cartesian_xyz);
    auto pnu_theta_phi = Transform::SphericalToPNU(spherical);
    pnu->GoToPoint(pnu_theta_phi.get<0>(), pnu_theta_phi.get<1>());
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
