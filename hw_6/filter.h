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
    void update() override;
    double value() const;

private:
    deque<double> _values;
    double _sum;
    int _count;
    double _running_average;
};

#endif
