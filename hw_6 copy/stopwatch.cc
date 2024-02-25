#include "stopwatch.h"

Stopwatch::Stopwatch() : running_(false) {}

void Stopwatch::start() {
    if (!running_) {
        start_time_ = std::chrono::high_resolution_clock::now();
        running_ = true;
    }
}

void Stopwatch::stop() {
    if (running_) {
        end_time_ = std::chrono::high_resolution_clock::now();
        running_ = false;
    }
}

void Stopwatch::reset() {
    running_ = false;
}

double Stopwatch::get_minutes() const {
    auto duration = running_ ? std::chrono::high_resolution_clock::now() - start_time_ : end_time_ - start_time_;
    return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<60>>>(duration).count();
}

double Stopwatch::get_seconds() const {
    auto duration = running_ ? std::chrono::high_resolution_clock::now() - start_time_ : end_time_ - start_time_;
    return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
}

double Stopwatch::get_milliseconds() const {
    auto duration = running_ ? std::chrono::high_resolution_clock::now() - start_time_ : end_time_ - start_time_;
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

double Stopwatch::get_nanoseconds() const {
    auto duration = running_ ? std::chrono::high_resolution_clock::now() - start_time_ : end_time_ - start_time_;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
}
