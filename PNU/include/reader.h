#ifndef DIPLOMA_READER_H
#define DIPLOMA_READER_H
#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "commands.h"
#include "transformer.h"

struct Position {
    double azimuth;
    double elevator;
};

class Reader{
public:
    explicit Reader(char* data);
    Position UnpackReply() const;
private:
    Position ReadState() const;
    Position GoToPoint() const;
    void MaxAccAndSpeed() const;
    void Reset() const;
    void ParseError(unsigned short code) const;
    void ParseUnitState(unsigned short unit_state) const;
    void ChangeIP() const;
    char* reply_;
};

#endif //DIPLOMA_READER_H
