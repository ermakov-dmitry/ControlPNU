#include "transformer.h"


namespace Transform {
    Spherical CartesianToPNU (const Cartesian& cartesian) {
      Spherical ret;
      ret.range = sqrt(pow(cartesian.x, 2.) + pow(cartesian.y, 2.) + pow(cartesian.z, 2.));
      ret.theta = 270 - 180 * atan2(sqrt(pow(cartesian.z, 2.)
                                         + pow(cartesian.x, 2.)), cartesian.y) / PI;

      ret.phi = 180 * atan2(cartesian.x, cartesian.z) / PI;
      if (ret.phi < 0) {
        ret.phi = 360.0 + ret.phi;
      }
      ret.phi = (ret.phi < 90) ? 360.0 - ret.phi : ret.phi - 90.0;
      return ret;
    }
}
