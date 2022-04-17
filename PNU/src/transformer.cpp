#include "transformer.h"


namespace Transform {
    Spherical CartesianToPNU (const Cartesian& cartesian) {
      Spherical ret;
      ret.range = sqrt(pow(cartesian.x, 2.) + pow(cartesian.y, 2.) + pow(cartesian.z, 2.));
      ret.theta = 270 - 180 * atan2(sqrt(pow(cartesian.z, 2.)
                                         + pow(cartesian.x, 2.)), cartesian.y) / PI;

      ret.phi = 180 * atan2(cartesian.z, cartesian.x) / PI;
      return ReduceAngles(ret);
    }

    Spherical ReduceAngles(const Spherical& in) {
      Spherical ret = in;
      double reduce_azimuth = in.phi - 360 * ((int)in.phi / 360);
      double reduce_elevator = in.theta - 360 * ((int)in.theta / 360);
      ret.phi = (reduce_azimuth < 0) ? 360 + reduce_azimuth : reduce_azimuth;
      ret.theta = (reduce_elevator < 0) ? 360 + reduce_elevator : reduce_elevator;
      return ret;
    }

    Spherical ReducePositiveAngles(const Spherical& in) {
      Spherical ret = ReduceAngles(in);
      ret.theta = (ret.theta > 180) ? ret.theta - 360 : ret.theta;
      ret.phi = (ret.phi > 180) ? ret.phi - 360 : ret.phi;
      return ret;
    }
}