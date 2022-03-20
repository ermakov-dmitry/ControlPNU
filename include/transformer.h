#ifndef DIPLOMA_TRANSFORMER_H
#define DIPLOMA_TRANSFORMER_H
#pragma once
#ifndef LOCAL_MACHINE
#include "global.h"
#else
#include <cmath>
#define PI M_PI
#endif

namespace Transform {
    struct Cartesian {
        double x;
        double y;
        double z;
    };

    struct Spherical {
        double range;
        double theta;
        double phi;
    };

    template<typename T>
    T RadToDeg(T rad) {
      return (rad * (180.0 / PI));
    }

    template<typename T>
    T DegToRad(T deg) {
      return (deg * (PI / 180.0));
    }

    template<typename T>
    double MkradToDeg(T mkrad) {
      return RadToDeg(static_cast<double>(mkrad) / 10000.0);
    }

    template<typename T>
    T DegToMkrad(double deg) {
      return static_cast<T>(DegToRad((deg * 10000)));
    }

    Spherical CartesianToPNU (const Cartesian&);

}


#endif //DIPLOMA_TRANSFORMER_H