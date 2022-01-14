#ifndef DIPLOMA_READER_H
#define DIPLOMA_READER_H
#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <cstdint>
#include <string>
#include "logger.h"
#include "commands.h"
#include "transformer.h"

class Reader{
    using data_ptr = std::unique_ptr<const std::vector<std::byte>>;
public:
    explicit Reader(bool is_print, bool is_log);
    void UnpackReply(data_ptr&&);

private:
    void ReadState(data_ptr&&);
    void GoToPoint(data_ptr&&);
    void MaxAccAndSpeed(data_ptr&&);
    void Reset(data_ptr&&);
    bool print_replies;
    bool log_replies;
    Logger logger_;
    Transformer transformer_;
    std::string print_message_;
    // std::shared_ptr<Command> log_command_;  // TODO create answer commands
};

#endif //DIPLOMA_READER_H
