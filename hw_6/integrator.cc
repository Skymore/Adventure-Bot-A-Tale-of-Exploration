#include "integrator.h"

void Integrator::update() {
    if (channel("link").nonempty()) {
        double val = channel("link").latest();
        _integral += val * delta();
        std::cout << "Integrator value: " << value() << std::endl;
    }
}

double Integrator::value() const {
    return _integral;
}