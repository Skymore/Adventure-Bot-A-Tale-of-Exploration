#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <elma/elma.h> // assuming elma is installed and configured
#include <iostream>

using namespace elma;

class Integrator : public Process {
public:
    Integrator(std::string name) : Process(name), _integral(0.0) {}
    void init() {}
    void start() {}
    void stop() {}
    void update() override;
    double value() const;

private:
    double _integral;
};

#endif
