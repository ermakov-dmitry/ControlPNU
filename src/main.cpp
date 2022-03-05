#include "objects.h"

std::unique_ptr<PNU> pnu;

void Init() {
    PNUCreator creator;
    creator.SetIPAddress("192.168.6.2").SetPort(10'000)
    .PrintReplies(true).LogReplies(true);
    std::unique_ptr<PNU> pnu_local = creator.CreatePNU();
    pnu.swap(pnu_local);
    pnu->Reset();
    pnu->ReadReply();
    pnu->GetState();
    pnu->GetState();
    pnu->ReadReply();
    Transform::Cartesian cartesian_xyz = {1, 1, 1};  // xyz coord
    auto pnu_theta_phi = Transform::CartesianToPNU(cartesian_xyz);
    pnu->GoToPoint(pnu_theta_phi.theta, pnu_theta_phi.phi);
    pnu->GetState();
}

void Calculate() {
    pnu->ReadReply();
    Transform::Cartesian cartesian_xyz = {1, 1, 1};  // xyz coord
    auto pnu_theta_phi = Transform::CartesianToPNU(cartesian_xyz);
    pnu->GoToPoint(pnu_theta_phi.theta, pnu_theta_phi.phi);
}

void Stop() {
    pnu->ReadReply();
}



int main() {
    /*Init();
    Calculate();
    Stop();*/
    using namespace Transform;
    Cartesian xyz{1, 0, 0};
    auto value = CartesianToPNU(xyz);
    return 0;
}
