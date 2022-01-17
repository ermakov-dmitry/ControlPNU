#ifndef DIPLOMA_SCENARIOS_H
#define DIPLOMA_SCENARIOS_H
#pragma once
#include "objects.h"
#include <chrono>

class Screenwriter {
public:
    explicit Screenwriter(PNU& pnu);
private:
    PNU& pnu_;
};

#endif //DIPLOMA_SCENARIOS_H
