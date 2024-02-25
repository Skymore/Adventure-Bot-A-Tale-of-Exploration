#include "filter.h"

void Filter::update() {
    if (channel("link").nonempty()) {
        double val = channel("link").latest();
        _values.push_back(val);
        _sum += val;
        if (_values.size() > 10) {
            _sum -= _values.front();
            _values.pop_front();
        }
        _running_average = _sum / _values.size();
        std::cout << "Filter average: " << _running_average << std::endl;
    }
}

double Filter::value() const {
    return _running_average;
}

