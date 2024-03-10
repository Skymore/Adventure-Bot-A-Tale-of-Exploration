#ifndef __TELEPORTER_AGENT__H
#define __TELEPORTER_AGENT__H 

#include "enviro.h"

using namespace enviro;

// The TeleporterController is responsible for handling teleportation
// and goal change events for the Teleporter agent.
class TeleporterController : public Process, public AgentInterface {

    public:
    TeleporterController() : Process(), AgentInterface() {}

    // Initialize the TeleporterController.
    void init() {
        // Listen for screen clicks to teleport the agent to the clicked position
        // and emit a goal change event with the new coordinates.
        watch("screen_click", [this](Event e) {
            teleport(e.value()["x"], e.value()["y"], 0);
            emit(Event("goal_change", { 
                { "x", e.value()["x"] }, 
                { "y", e.value()["y"] } 
            }));
        });

        // Listen for the goal_reached event to randomly teleport the agent
        // within a specified range and emit a new goal_change event.
        watch("goal_reached", [this](Event e) {
            int x = rand() % 400 - 200; // Generate a new x-coordinate.
            int y = rand() % 400 - 200; // Generate a new y-coordinate.
            printf("goal reached, teleport to %d, %d\n", x, y); // Log the teleportation.
            teleport(x, y, 0); // Teleport the agent.
            emit(Event("goal_change", { 
                { "x", x }, 
                { "y", y } 
            })); // Emit a new goal_change event.
        });
    }

    void start() {}
    void update() {}
    void stop() {}

};

// The Teleporter agent is defined with the TeleporterController process.
// It represents an agent that can be teleported to different positions within the simulation.
class Teleporter : public Agent {

    public:
    Teleporter(json spec, World& world) : Agent(spec, world) {
        add_process(bc); // Add the TeleporterController process.
    }
    private:
    TeleporterController bc; // Instance of the TeleporterController.

};

DECLARE_INTERFACE(Teleporter)

#endif
