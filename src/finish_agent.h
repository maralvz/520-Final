#ifndef __FINISH_AGENT_AGENT__H
#define __FINISH_AGENT_AGENT__H 

#include "enviro.h"

using namespace enviro;

class finishAgentController : public Process, public AgentInterface {

    public:
    finishAgentController() : Process(), AgentInterface() {}

    void init() {
        // Only function. Object there just to detect whether the user got there in time or not
        notice_collisions_with("userRobot", [&](Event e) {
            emit(Event("madeit"));
        });
    }
    void start() {}
    void update() {}
    void stop() {}

};

class finishAgent : public Agent {
    public:
    finishAgent(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    finishAgentController c;
};

DECLARE_INTERFACE(finishAgent)

#endif