#ifndef DIPLOMA_TRANSFORMER_H
#define DIPLOMA_TRANSFORMER_H
#pragma once
#include <cmath>

namespace Transform {
    struct Cartesian {
        long double x;
        long double y;
        long double z;
    };

    struct Spherical {
        long double range;
        long double theta;
        long double phi;
    };

    template<typename T>
    [[nodiscard]] T RadToDeg(T rad) {
        return (rad * (180.0 / M_PI));
    }

    template<typename T>
    [[nodiscard]] T DegToRad(T deg) {
        return (deg * (M_PI / 180.0));
    }

    template<typename T>
    long double MkradToDeg(T mkrad) {
        return RadToDeg(static_cast<double>(mkrad) / 10000.0);
    }

    template<typename T>
    T DegToMkrad(long double deg) {
        return static_cast<T>(DegToRad((deg * 10000)));
    }

    [[nodiscard]] Spherical CartesianToPNU (const Cartesian&);

}


#endif //DIPLOMA_TRANSFORMER_H
