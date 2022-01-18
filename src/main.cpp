#include "objects.h"
#include "scenarios.h"

int main() {
    PNUCreator creator;
    creator.SetIPAddress("192.168.6.2")
            .SetPort(10'000)
            .PrintReplies(true)
            .LogReplies(true);
    PNU pnu = creator.CreatePNU();
    ScreenwriterBuilder builder;
    builder.SetTargetXStart(1)
            .SetTargetYStart(2)
            .SetTargetZStart(3);
    Screenwriter screenwriter = builder.CreateScreenwriter(pnu);
    // screenwriter.TargetLinearMotion();
    pnu.Reset();
    pnu.GetState();
    pnu.GoToPoint(45, 135);
    pnu.GetState();
    pnu.Reset();
    return 0;
}
