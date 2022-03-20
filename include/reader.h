#ifndef DIPLOMA_READER_H
#define DIPLOMA_READER_H
#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "commands.h"
#include "transformer.h"

class Reader{
public:
    explicit Reader(bool is_print, char* data);
    void UnpackReply();

private:
    void ReadState();
    void GoToPoint();
    void MaxAccAndSpeed();
    void Reset();
    void ParseError(unsigned short code) const;
    void ParseUnitState(unsigned short unit_state) const;
    char* reply_;
    bool print_replies;
    std::string print_message_;
    std::vector<std::string> log_command_;  // TODO create answer commands
};

#endif //DIPLOMA_READER_H