#include "random_process.h"

void RandomProcess::update() {
        double random_value = (double)rand() / RAND_MAX; 
        channel("link").send(random_value);
    }