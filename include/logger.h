#ifndef DIPLOMA_LOGGER_H
#define DIPLOMA_LOGGER_H
#pragma once
#include <string_view>
#include <memory>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>

class Logger {
public:
    Logger();
    void LogStateErrors(std::string_view errors);
    void LogStateCriticalErrors(std::string_view critical_errors);
    void LogMoveUnitState(std::string_view state);
    void LogData(std::unique_ptr<std::vector<std::string>>&& data);
    ~Logger();

private:
    std::chrono::steady_clock::time_point start_time_ = std::chrono::steady_clock::now();
    std::ofstream log_;
    std::ofstream errors_;
};

#endif //DIPLOMA_LOGGER_H
