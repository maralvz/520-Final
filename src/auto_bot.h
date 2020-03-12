#ifndef __AUTO_BOT_AGENT__H
#define __AUTO_BOT_AGENT__H 

#include "enviro.h"
#include <string>
#include <math.h>

using namespace enviro;

namespace {
    class MovingForward : public State, public AgentInterface {
        public:
        void entry(const Event& e) {}
        void during() {
            track_velocity(10,0);
            if (sensor_value(0) < 30 || sensor_value(1) < 15 || sensor_value(2) < 15) {
                emit(Event(ring));
            }
        }
        void exit(const Event& e) {}
        void set_ring(std::string s) {
            ring = s;
        }
        std::string ring;
    };

    class Rotating : public State, public AgentInterface {
        public:
        void entry(const Event& e) {
            rotVela = 1;
            rotVelb = -1;
        }
        void during() {
            if (sensor_value(1) == sensor_value(2)) {
                track_velocity(0,0);
            }
            if (sensor_value(1) > sensor_value(2)) {
                track_velocity(0, rotVela);
                if (sensor_value(0) > 60) {
                    emit(Event(ring));
                }
            } else {
                track_velocity(0,rotVelb);
                if (sensor_value(0) > 60) {
                    emit(Event(ring));
                }
            }
        }
        void exit(const Event& e) {}
        double rotVela;
        double rotVelb;
        void set_ring(std::string s) {
            ring = s;
        }
        std::string ring;
    };

    class MyRobotController : public StateMachine, public AgentInterface {
        public:
        MyRobotController() : StateMachine() {
            set_initial(fwd);
            ring = "ring_" + std::to_string(rand()%1000);
            add_transition(ring, fwd, rot);
            add_transition(ring, rot, fwd);
            fwd.set_ring(ring);
            rot.set_ring(ring);

        }

        MovingForward fwd;
        Rotating rot;
        std::string ring;
    };

    class MyRobot : public Agent {
        public:
        MyRobot(json spec, World& world) : Agent(spec, world) {
            add_process(c);
        }
        private:
        MyRobotController c;
    };
    
    DECLARE_INTERFACE(MyRobot)
}
#endif