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

class Reader{
    using data_ptr = std::unique_ptr<const std::vector<std::byte>>;
public:
    explicit Reader(bool is_print, bool is_log);
    void DefineReply(data_ptr&&) const;

private:
    void ReadState(data_ptr&&) const;
    void GoToPoint(data_ptr&&) const;
    void MaxAccAndSpeed(data_ptr&&) const;
    void Reset(data_ptr&&) const;
    bool print_replies;
    bool log_replies;
    Logger logger_;
    std::string print_message_;
    // std::shared_ptr<Command> log_command_;  // TODO create answer commands
};

#endif //DIPLOMA_READER_H
