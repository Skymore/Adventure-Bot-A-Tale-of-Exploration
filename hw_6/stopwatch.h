#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>

class Stopwatch {
public:
    Stopwatch();

    void start();
    void stop();
    void reset();
    double get_minutes() const;
    double get_seconds() const;
    double get_milliseconds() const;
    double get_nanoseconds() const;

private:
    std::chrono::high_resolution_clock::time_point start_time_;
    std::chrono::high_resolution_clock::time_point end_time_;
    bool running_;
};

#endif // STOPWATCH_H
