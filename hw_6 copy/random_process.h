#ifndef RANDOM_PROCESS_H
#define RANDOM_PROCESS_H

#include <elma/elma.h> // assuming elma is installed and configured
#include <random>
#include <iostream>

using namespace elma;

class RandomProcess : public Process {
public:
    RandomProcess(std::string name) : Process(name) {}
    void init() {}
    void start() {}
    void stop() {}
    void update() {
        double random_value = (double)rand() / RAND_MAX; 
        channel("link").send(random_value);
    }

private:
};

#endif
