#include "transformer.h"


namespace Transform {
    namespace bg = boost::geometry;

    bg::model::point<long double,
            3, bg::cs::cartesian> CartesianToAvia(const bg::model::point<long double,
            3, bg::cs::cartesian>& cartesian_xyz) {

        return {cartesian_xyz.get<1>(), cartesian_xyz.get<2>(), cartesian_xyz.get<0>()};
    }

    bg::model::point<long double, 3, bg::cs::spherical<bg::degree>>
    CartesianToSpherical(const bg::model::point<long double,
            3, bg::cs::cartesian>& cartesian_xyz) {
        bg::model::point<long double, 3, bg::cs::spherical<bg::degree>> sphere{};
        bg::transform(cartesian_xyz, sphere);
        return sphere;
    }

    boost::geometry::model::point<long double,
            2, boost::geometry::cs::spherical<boost::geometry::degree>> SphericalToPNU(
            const boost::geometry::model::point<long double, 3,
                    boost::geometry::cs::spherical<boost::geometry::degree>> &spherical) {
        // TODO
        // transform from spherical to PNU azimuth and elevator
        return {spherical.get<0>(), 270.0 - spherical.get<1>()};
    }

    boost::geometry::model::point<long double,
            3, boost::geometry::cs::cartesian> AviaToCartesian(
            const boost::geometry::model::point<long double, 3, boost::geometry::cs::cartesian>& avia_xyz) {
        return {avia_xyz.get<2>(), avia_xyz.get<0>(), avia_xyz.get<1>()};
    }
}

