#ifndef DIPLOMA_SCENARIOS_H
#define DIPLOMA_SCENARIOS_H
#pragma once
#include "objects.h"
#include <chrono>

class ScreenwriterBuilder;

class Screenwriter {
public:
    friend ScreenwriterBuilder;
    void TargetLinearMotion();
private:
    explicit Screenwriter(PNU& pnu, long double x, long double y, long double z);
    PNU& pnu_;
    Target target_;
    Transformer transformer_;
};

class ScreenwriterBuilder {
public:
    ScreenwriterBuilder& SetTargetXStart(long double x);
    ScreenwriterBuilder& SetTargetYStart(long double y);
    ScreenwriterBuilder& SetTargetZStart(long double z);
    Screenwriter CreateScreenwriter(PNU& pnu);
private:
    long double x_ = 0;
    long double y_ = 0;
    long double z_ = 0;
};

#endif //DIPLOMA_SCENARIOS_H
