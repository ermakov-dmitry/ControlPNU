#include "objects.h"

int main() {
    PNU device("192.168.59.218", 10000);
    //! Test all methods
    device.Reset();
    device.ReadReply();
    device.GetState();
    device.ReadReply();
    device.GoToPoint(45, 30);
    device.SetMaxAccelerationAndSpeed({100,
                                       100,
                                       100,
                                       100});
    device.ReadReply();
    device.GetOutput();
    device.SetOffsetsAndBounds({}, {});
    device.ReadReply();
    /*
    device.ChangeIPAddress(192.168.59.218");  Warning!
     */
    //! Do whatever your soul desires :)
    return 0;
}
