#ifndef __TELEPORT_AGENT_AGENT__H
#define __TELEPORT_AGENT_AGENT__H 

#include "enviro.h"

using namespace enviro;

// Class that simply responds to a collision with the user robot and 
// emits an event.
class teleportAgentController : public Process, public AgentInterface {

    public:
    teleportAgentController() : Process(), AgentInterface() {}

    void init() {
        // Object just there so that it can transport the user-controlled robot "downstairs"
        notice_collisions_with("userRobot", [&](Event e) {
            emit(Event("transport"));
        });
    }
    void start() {}
    void update() {}
    void stop() {}

};

class teleportAgent : public Agent {
    public:
    teleportAgent(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    teleportAgentController c;
};

DECLARE_INTERFACE(teleportAgent)

#endif