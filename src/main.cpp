#include "objects.h"

int main() {
    PNUCreator creator;
    creator.SetIPAddress("192.168.6.2").SetPort(10'000).PrintReplies(true).LogReplies(false);
    PNU pnu = creator.CreatePNU();
    pnu.Reset();
    pnu.GetState();
    pnu.GetState();
    pnu.GoToPoint(45, 135);
    pnu.GetState();
    pnu.Reset();
    return 0;
}
