#ifndef DIPLOMA_LOGGER_H
#define DIPLOMA_LOGGER_H
#pragma once
#include <string_view>
#include <memory>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>

class Logger {
public:
    Logger();
    void LogStateErrors(const std::string& errors);
    void LogStateCriticalErrors(const std::string& critical_errors);
    void LogMoveUnitState(const std::string& state);
    void LogData(std::vector<std::string>&& data);
    ~Logger();

private:
    std::chrono::steady_clock::time_point start_time_ = std::chrono::steady_clock::now();
    std::ofstream log_;
    std::ofstream errors_;
    std::ofstream move_state_;
};

#endif //DIPLOMA_LOGGER_H
