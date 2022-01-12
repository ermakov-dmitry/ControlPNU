#ifndef DIPLOMA_TRANSFORMER_H
#define DIPLOMA_TRANSFORMER_H
#pragma once
#include <boost/geometry/geometry.hpp>
#include <cmath>

class Transformer {

public:
    template<typename T>
    [[nodiscard]] T RadToDeg(T rad) const {
        return (rad * (180.0 / M_PI));
    }

    template<typename T>
    [[nodiscard]] T DegToRad(T deg) const {
        return (deg * (M_PI / 180.0));
    }

    template<typename T>
    long double MkradToDeg(T mkrad) const {
        return RadToDeg(static_cast<double>(mkrad) / 10'000.0);
    }

    template<typename T>
    T DegToMkrad(long double deg) const {
        return static_cast<T>(DegToRad((deg * 10'000)));
    }

    [[nodiscard]] static boost::geometry::model::point<long double,
    3, boost::geometry::cs::cartesian> CartesianToAvia(const boost::geometry::model::point<long double,
            3, boost::geometry::cs::cartesian>& cartesian_xyz);

    [[nodiscard]] static boost::geometry::model::point<long double,
    3, boost::geometry::cs::spherical<boost::geometry::degree>>
    CartesianToSpherical (const boost::geometry::model::point<long double,
            3, boost::geometry::cs::cartesian>& cartesian_xyz);

    [[nodiscard]] static boost::geometry::model::point<long double,
            2, boost::geometry::cs::spherical<boost::geometry::degree>>
    SphericalToPNU (const boost::geometry::model::point<long double,
            3, boost::geometry::cs::spherical<boost::geometry::degree>>& spherical);
};


#endif //DIPLOMA_TRANSFORMER_H
