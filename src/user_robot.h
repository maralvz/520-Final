#ifndef __USER_ROBOT_AGENT__H
#define __USER_ROBOT_AGENT__H 

#include "enviro.h"

using namespace enviro;

class userRobotController : public Process, public AgentInterface {

    public:
    userRobotController() : Process(), AgentInterface() {}

    void init() {
        watch("keyup", [&](Event &e) {
            auto keyB = e.value()["key"].get<std::string>();
            if (keyB == "t") {
                x_force = 0;
                y_force = -forceMag;
            } else if (keyB == "v") {
                x_force = 0;
                y_force = forceMag;
            } else if (keyB == "f") {
                x_force = -forceMag;
                y_force = 0;
            } else if (keyB == "h") {
                x_force = forceMag;
                y_force = 0;
            } else {
                x_force = 0;
                y_force = 0;
            }
            omni_apply_force(x_force, y_force);
        });
    }

    void start() {
        x_force = 0;
        y_force = 0;
    }
    void update() {
        omni_damp_movement();
    }
    void stop() {}
    double x_force, y_force;
    const double forceMag = 30;

};

class userRobot : public Agent {
    public:
    userRobot(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    userRobotController c;
};

DECLARE_INTERFACE(userRobot)

#endif