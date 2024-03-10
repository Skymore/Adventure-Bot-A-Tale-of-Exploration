#ifndef __BOX_AGENT__H
#define __BOX_AGENT__H

#include "enviro.h"
#include <chrono>
#include <random>

using namespace enviro;
using namespace std::chrono;

class box2Controller : public Process, public AgentInterface {
public:
    boxController() : Process(), AgentInterface() {
        // 初始化随机数生成器
        std::random_device rd; // 随机数种子
        gen = std::mt19937(rd()); // 用于生成随机数的引擎
        dist_x = std::uniform_int_distribution<>(-200, 200); // x坐标的随机分布
        dist_y = std::uniform_int_distribution<>(-200, 200); // y坐标的随机分布

        // 记录初始时间点
        start_time = std::chrono::steady_clock::now();
    }

    void update() override {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count();
        if (elapsed >= 10) {
            // 每10秒更新位置
            double new_x = dist_x(gen);
            double new_y = dist_y(gen);
            teleport(new_x, new_y, 0);
            start_time = now; // 重置时间点
        }
    }
    void init() {}
    void start() {}
    void stop() {}

private:
    std::mt19937 gen;
    std::uniform_int_distribution<> dist_x, dist_y;
    std::chrono::steady_clock::time_point start_time;
};


class box2 : public Agent {
public:
    box(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
private:
    box2Controller c;
};

DECLARE_INTERFACE(box2)

#endif
