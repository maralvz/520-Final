#ifndef __AUTO_BOT_AGENT__H
#define __AUTO_BOT_AGENT__H 

#include "enviro.h"
#include <string>
#include <math.h>

using namespace enviro;

namespace {
    // Class that controls the auto-bot moving through the lower
    // maze. 
    class MovingForward : public State, public AgentInterface {
        public:
        void entry(const Event& e) {}
        void during() {
            // If auto-bot gets to the final destination before the user, the event is sent 
            // so that the user_robot gets "grounded"
            cpVect pos = position();
            double xCoord = pos.x;
            double yCoord = pos.y;
            if (xCoord > 300 && yCoord > -40 ) {
                emit(Event("grounded"));
            }
            // Normal forward movement of the robot under normal conditions
            track_velocity(15,0);
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
            rotVela = 2;
            rotVelb = -2;
        }
        void during() {
            // should it happen that both sensor values are exactly the same, stop
            // moving. All else, rotate depending on the space available.
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