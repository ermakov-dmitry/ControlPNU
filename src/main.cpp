#include <iostream>
#include "objects.h"

int main() {
    PNUCreator creator;
    creator.SetIPAddress("192.168.6.2").SetPort(10'000).PrintReplies(true).LogReplies(true);
    PNU pnu = creator.CreatePNU();
    pnu.GetState();
    return 0;
}
