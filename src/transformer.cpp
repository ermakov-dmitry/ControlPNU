#include "transformer.h"


namespace Transform {
    Spherical CartesianToPNU (const Cartesian& cartesian) {
        Spherical ret{};
        ret.range = sqrtl(powl(cartesian.x, 2.) + powl(cartesian.y, 2.) + powl(cartesian.z, 2.));
        ret.theta = 180 * atan2l(sqrtl(powl(cartesian.z, 2.)
                + powl(cartesian.x, 2.)), cartesian.y) / M_PI;
        ret.phi = 180 * atan2l(cartesian.x, cartesian.z) / M_PI;  // 270 - atan
        return ret;
    }
}

