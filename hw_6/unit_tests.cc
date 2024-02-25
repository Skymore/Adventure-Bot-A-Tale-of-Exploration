#include <assert.h>
#include <thread>

#include "filter.h"
#include "integrator.h"
#include "random_process.h"
#include "stopwatch.h"

#include "elma/elma.h"
#include "gtest/gtest.h"

#define MS(__ms__) high_resolution_clock::duration(milliseconds(__ms__))
#define SLEEP std::this_thread::sleep_for(std::chrono::milliseconds(3000))

namespace {

using namespace elma;

TEST(StopWatch, StopWatchTest) {
    Stopwatch w;
    w.start();
    SLEEP;
    w.stop();
    std::cout << w.get_minutes() << "m"
              << "\n";
    std::cout << w.get_seconds() << "s"
              << "\n";
    std::cout << w.get_milliseconds() << "ms"
              << "\n";
    std::cout << w.get_nanoseconds() << "ns"
              << "\n";
    ASSERT_NEAR(w.get_minutes(), 0.05, 0.0005);
    ASSERT_NEAR(w.get_seconds(), 3, 0.003);
    ASSERT_NEAR(w.get_milliseconds(), 3000, 30);
    long nano_seconds = 3000000000;
    ASSERT_NEAR(w.get_nanoseconds(), nano_seconds, nano_seconds/100);
    ASSERT_NEAR(w.get_seconds(), 3, 0.003);
    w.reset();
}

TEST(ProcessTest, RandomProcessAndFilter) {
    Manager m;
    Channel link("link");

    RandomProcess r("random numbers");
    Filter f("filter");

    m.schedule(r, MS(100))
        .schedule(f, MS(100))
        .add_channel(link)
        .init()
        .run(MS(1000));

    std::cout << "avg: " << f.value() << std::endl;
}

TEST(ProcessTest, IntegratorTest) {
    Manager m;
    Channel link("link");

    RandomProcess r("random numbers");
    Integrator i("integrator");

    m.schedule(r, MS(100))
        .schedule(i, MS(100))
        .add_channel(link)
        .init()
        .run(MS(1000));

    std::cout << "integral: " << i.value() << std::endl;
}
}  // namespace