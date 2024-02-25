#ifndef FILTER_H
#define FILTER_H

#include <elma/elma.h> // assuming elma is installed and configured
#include <deque>
#include <iostream>

using namespace elma;
using namespace std;

class Filter : public Process {
public:
    Filter(string name) : Process(name), _sum(0.0), _count(0) {}
    void init() {}
    void start() {}
    void stop() {}
    void update() {
        if (channel("link").nonempty()) {
            double val = channel("link").latest();
            _values.push_back(val);
            _sum += val;
            if (_values.size() > 10) {
                _sum -= _values.front();
                _values.pop_front();
            }
            _running_average = _sum / _values.size();
            cout << "Filter average: " << _running_average << endl;
        }
    }
    double value() const {
        return _running_average;
    }

private:
    deque<double> _values;
    double _sum;
    int _count;
    double _running_average;
};

#endif
