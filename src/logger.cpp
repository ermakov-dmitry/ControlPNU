#include "logger.h"

using namespace std::chrono;
using namespace std;

void Logger::LogStateErrors(string_view errors) {
    auto dur = steady_clock::now() - start_time_;
    errors_ << duration_cast<seconds>(dur).count() << " seconds:\n" << errors;
}

void Logger::LogStateCriticalErrors(string_view critical_errors) {
    auto dur = steady_clock::now() - start_time_;
    errors_ << duration_cast<seconds>(dur).count() << " seconds:\n" << critical_errors;
}

void Logger::LogData(unique_ptr<vector<string>>&& data) {
    auto dur = steady_clock::now() - start_time_;
    log_ << duration_cast<milliseconds>(dur).count();
    for (const auto& value : *data) {
        log_ << ',' << value;
    }
    log_ << '\n';
}

void Logger::LogMoveUnitState(string_view state) {
    auto dur = steady_clock::now() - start_time_;
    move_state_ << duration_cast<seconds>(dur).count() << " seconds:\n" << state;
}

Logger::~Logger() {
    log_.close();
    errors_.close();
    move_state_.close();
}

Logger::Logger() {
    log_.open("../log/log.csv");
    errors_.open("../log/errors.log");
    move_state_.open("../log/move_state.log");
    log_.clear();
    errors_.clear();
    move_state_.clear();
    log_ << "time(ms),code,data\n";
}

