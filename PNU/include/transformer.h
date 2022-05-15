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
    //! Структура декартовых координат
    struct Cartesian {
      double x;
      double y;
      double z;
    };
    //! Структура сферических координат
    struct Spherical {
      double range;
      double theta;
      double phi;
    };
    //! Перевод из радиан в градусы
    template<typename T>
    T RadToDeg(T rad) {
      return (rad * (180.0 / PI));
    }
    //! Перевод из градусов в радианы
    template<typename T>
    T DegToRad(T deg) {
      return (deg * (PI / 180.0));
    }
    //! Перевод из 10^(-4) радиан в градусы
    template<typename T>
    double MkradToDeg(T mkrad) {
      return RadToDeg(static_cast<double>(mkrad) / 10000.0);
    }
    //! Перевод из градусов в 10^(-4) радиан
    template<typename T>
    T DegToMkrad(double deg) {
      return static_cast<T>(DegToRad((deg * 10000)));
    }
    //! Перевод из связанной СК в сферическую ПНУ
    Spherical CartesianToPNU(const Cartesian&);
    //! Приведение углов в диапазон [0; 360)
    Spherical ReduceAngles(const Spherical&);
    //! Приведение углов в диапазон (-180; 180]
    Spherical ReducePositiveAngles(const Spherical&);
}


#endif //DIPLOMA_TRANSFORMER_H