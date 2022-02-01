#include "objects.h"
#include "modes.h"

int main() {
    PNUCreator creator;
    creator.SetIPAddress("192.168.6.2")
            .SetPort(10'000)
            .PrintReplies(true)
            .LogReplies(true);
    PNU pnu = creator.CreatePNU();
    ModesBuilder builder;
    builder.SetTargetXStart(100)
            .SetTargetYStart(-500)
            .SetTargetZStart(100);
    Modes modes = builder.CreateModes(pnu);
    modes.TargetLinearMotion();
    return 0;
}
