#ifndef __MY_ROBOT_AGENT__H
#define __MY_ROBOT_AGENT__H

#include "enviro.h"

using namespace enviro;

// State for moving towards the goal
class MovingForward : public State, public AgentInterface {
public:
    MovingForward() : goal_x(0), goal_y(0) {}

    // Update the goal location
    void update_goal(double x, double y) {
        goal_x = x;
        goal_y = y;
    }

    void entry(const Event& e) override {}

    // During this state, move towards the goal and check for obstacles
    void during() override {
        move_toward(goal_x, goal_y);
        // If an obstacle is detected close by, switch to the obstacle handling state
        if (sensor_value(5) < 50) {
            emit(Event(tick_name+"_obstacle"));
        }

        // Check if the goal is reached
        if (abs(x() - goal_x) < 40 && abs(y() - goal_y) < 40) {
            printf("goal reached\n");
            emit(Event("goal_reached"));
        }
    }

    void exit(const Event& e) override {}

    // Used to set a unique identifier for state transition events
    void set_tick_name(std::string s) { tick_name = s; }
    std::string tick_name;

private:
    double goal_x, goal_y;
};

// State for rotating to avoid obstacles
class Rotating : public State, public AgentInterface {
public:
    Rotating() : has_chosen_direction(false), goal_x(0), goal_y(0) {}

    // Update the goal location
    void update_goal(double x, double y) {
        goal_x = x;
        goal_y = y;
    }

    // Entry action for Rotating state
    void entry(const Event& e) override {
        // Choose a direction to rotate only once upon entering this state
        if (!has_chosen_direction) {
            choose_direction();
            has_chosen_direction = true;
        }
    }

    // During Rotating state, continue rotating and check for clear path
    void during() override {
        track_velocity(0, rate);
        // If there's no obstacle ahead, switch back to moving forward
        if (sensor_value(5) > 140) {
            emit(Event(tick_name + "_clear"));
            has_chosen_direction = false;
        }

        // Check if the goal is reached
        if (abs(x() - goal_x) < 40 && abs(y() - goal_y) < 40) {
            printf("goal reached\n");
            emit(Event("goal_reached"));
        }
    }

    void exit(const Event& e) override {
        decorate("");
        clear_label();
        has_chosen_direction = false;
    }

    // Choose the direction of rotation based on sensor values
    void choose_direction() {
        double left_distance = sensor_value(0);
        double right_distance = sensor_value(8);
        rate = left_distance > right_distance ? -2 : 2;
    }

    void set_tick_name(std::string s) { tick_name = s; }
    std::string tick_name;

private:
    double rate;
    bool has_chosen_direction;
    double goal_x, goal_y;
};

// Controller class managing the states of the robot
class MyRobotController : public StateMachine, public AgentInterface {
public:
    MyRobotController() : StateMachine(), goal_x(0), goal_y(0) {
        set_initial(moving_forward);
        tick_name = "tick_" + std::to_string(rand() % 1000);
        
        // Define state transitions based on events
        add_transition(tick_name+"_obstacle", moving_forward, rotating); 
        add_transition(tick_name+"_clear", rotating, moving_forward); 
        
        moving_forward.set_tick_name(tick_name);
        rotating.set_tick_name(tick_name);
    }

    // Initialize state machine and watch for goal_change events
    void init() override {
        watch("goal_change", [this](Event e) {
            goal_x = e.value()["x"];
            goal_y = e.value()["y"];
            moving_forward.update_goal(goal_x, goal_y);
            rotating.update_goal(goal_x, goal_y);
        });
        StateMachine::init();
    }

    MovingForward moving_forward;
    Rotating rotating;
    std::string tick_name;
    double goal_x, goal_y;
};

// Main agent class
class MyRobot : public Agent {
public:
    MyRobot(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
private:
    MyRobotController c;
};

DECLARE_INTERFACE(MyRobot)

#endif
