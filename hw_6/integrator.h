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
    void update() {
        if (channel("link").nonempty()) {
            double val = channel("link").latest();
            _integral += val * delta();
            std::cout << "Integrator value: " << value() << std::endl;
        }
    }
    double value() const {
        return _integral;
    }

private:
    double _integral;
};

#endif
