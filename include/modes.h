#ifndef DIPLOMA_MODES_H
#define DIPLOMA_MODES_H
#pragma once
#include "objects.h"
#include <chrono>

class ModesBuilder;

class Modes {
public:
    friend ModesBuilder;
    void TargetLinearMotion();
private:
    explicit Modes(PNU& pnu, long double x, long double y, long double z);
    PNU& pnu_;
    Target target_;
    Transformer transformer_;
};

class ModesBuilder {
public:
    ModesBuilder& SetTargetXStart(long double x);
    ModesBuilder& SetTargetYStart(long double y);
    ModesBuilder& SetTargetZStart(long double z);
    Modes CreateModes(PNU& pnu) const;
private:
    long double x_ = 0;
    long double y_ = 0;
    long double z_ = 0;
};

#endif //DIPLOMA_MODES_H
