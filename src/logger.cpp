#include "logger.h"

using namespace std::chrono;

void Logger::LogStateErrors(std::string_view errors) {
    auto dur = steady_clock::now() - start_time_;
    errors_ << duration_cast<seconds>(dur).count() << ": " << errors;
}

void Logger::LogStateCriticalErrors(std::string_view critical_errors) {
    auto dur = steady_clock::now() - start_time_;
    errors_ << duration_cast<seconds>(dur).count() << ": " << critical_errors;
}

void Logger::LogData(std::unique_ptr<std::vector<std::string>>&& data) {
    auto dur = steady_clock::now() - start_time_;
    log_ << duration_cast<seconds>(dur).count();
    for (const auto& value : *data) {
        log_ << ',' << value;
    }
}

void Logger::LogMoveUnitState(std::string_view critical_errors) {
    auto dur = steady_clock::now() - start_time_;
    errors_ << duration_cast<seconds>(dur).count() << ": " << critical_errors;
}

Logger::~Logger() {
    log_.close();
    errors_.close();
}

Logger::Logger() {
    log_.open("../log/log.csv");
    errors_.open("../log/errors.log");
    log_.clear();
    errors_.clear();
}

