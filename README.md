Don't Tell Mom!
===

Software Engineering for Embedded Applications
===

Winter 2020 - Final Project EEP520
---

In this repository I present the completed final project for the EEP520 course taken at the University of Washington. The full project installation, usage, capabilities, code and simulation are discussed further down in this file. Simply put, the project completed is a maze with two built-in robots. One autonomously drives itself through the maze and the other can be manually controlled by the user to get to a common final destination. Visual representations of the simulation can be found in the `Image` folder located in this directory. I decided to name this project: `Mazed`. 

Installation
---

`Mazed ` runs solely due to the help of two packages built by the course Instructor called ELMA and ENVIRO. To run this project you will need to call these packages; click [here](https://github.com/klavinslab/elma) and [here](https://github.com/klavinslab/enviro) for more information on ELMA and ENVIRO respectively. The instructor made these packages available through [Docker](https://www.docker.com) which I recommend installing to virtually access these packages. Once Docker or these packages have been installed in your computer, simply download this repository to your computer and open with the IDE of preference. <br />

You may download this repository and access the the directory by running (in a directory you created): <br />
```bash
git clone https://github.com/maralvz/520-Final.git
cd 520-Final
```

Usage
---

To run ELMA/ENVIRO's enviroment, move through the terminal to the directory `520-Final`, where this entire repository is located at and run:<br />
```bash
docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.4 bash
```
For this project, I used ENVIRO's version 1.4 but you may find information on other versions in the ENVIRO's repository. Once this command is entered, you should now be operating within a Docker container using ELMA/ENVIRO. At this point, from within the main directory, simply enter: `esm start`. This will start broadcasting to a localhost channel. In a web-browser open a new tab and enter: `localhost`. At this point you should see in localhost that the "server" is not running, this is because the simulation has not been started yet. To start it simply enter in the terminal: `enviro`, and this should immediately display the simulation of `Don't Tell Mom` game. <br />

In the game you, the small circled object, are the small brother and the bigger circle is your bigger brother. Your task is to get to your mom's bedroom (green square) before your brother does. If you do, you win, if you don't, you'll be grounded and no video games for you for a week! Could you beat your brother? Note than you need to go down the stairs which is represented by the brown square at the end of the first maze. Hit the brown rectangle to go downstairs and beat your brother!

To control the manual robot, use keys "t" for up, "v" for down, "f" for left, and "h" for right. You can shutdown the simulation at anytime by simply using `CTRL + c`. To restart the simulation re-enter `enviro`. 

Classes Description
===

Teleporting
---

Both `.h` files: `teleport_agent` and `finish_agent` have the exact same functionality but the final purpose is different. All implementations for these two files were made on the `.h` file. Simply, the file were left as they were created when the `esm generate` command is used (refer to ENVIRO documentation for further explanation). The only thing that was changed was the `init` function which instead of being blank, the `notice_collisions_with` function was used to send out an Event whenever the manually-controlled robot collides with it. The implementation looks as follows: <br />

```c++
void init() {
        notice_collisions_with("userRobot", [&](Event e) {
            emit(Event("transport"));
        });
    }
``` 
The difference between these is that the 'teleport_agent' was made so that the user robot would teleport to the second part of the maze, and the 'finish_agent' so that the player is notified that it achieved the goal.

Manual Robot
---

The manual robot (user_robot) functionalities are controlled by the class `userRobotController`. This class not only listens and responds to the Events sent by 'finish_agent' and 'teleport_agent', but it also moves the robot as a response to user-keyboard entries. The class looks as follows: <br />
```c++
class userRobotController : public Process, public AgentInterface {

    public:
    userRobotController() : Process(), AgentInterface() {}

    void init() {
        watch("grounded", [&](Event e) {
            label("I'm grounded", 10, 0);
            teleport(-305, 320, 0);
        });
        watch("transport", [&](Event e) {
            teleport(-305, 320, 0);
        });
        watch("madeit", [&](Event e) {
            label("I'm safe", -10, 10);
        });
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
```

Auto-Robot
---

The auto-bot movement is being controlled by two main classes: `movingForward` and `Rotating`. By setting up the switches from class to class in the `MyRobotController` class, these class interchange from one to another by events which are reading from the sensors located in front of the robot. Comments have been inserted in the code for further explanation (see .h file). The classes mentioned are depicted below: <br />
```c++
class MovingForward : public State, public AgentInterface {
        public:
        void entry(const Event& e) {}
        void during() {
            cpVect pos = position();
            double xCoord = pos.x;
            double yCoord = pos.y;
            if (xCoord > 300 && yCoord > -40 ) {
                emit(Event("grounded"));
            }
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
```


Visuals
---

For a visual representation of what you should be seeing when running the simulation, simply enter the `Images` folder in this directory. 

License
---

This repository contains open-source code which is governed by the MIT license. 

Other Information
===

References
---

The functionality of the project overall was accomplished by using as reference the ENVIRO package examples and the use instructions.

Challenges
---

As the final project came together, and being entirely new to programming, I encountered challenges with the development of the maze-map and the proper movements of the auto-robot. First, it took me a very long time to put the maze map together; not only the physical walls but getting the dimensions right so that the autobot had enough room to freely roam while still moving towards the final target. Second, the logic behid having the auto-bot move freely, yet, continuously making progress towards the end was difficult to for me. One thing I wanted to add but couldn't was the functionality of getting the auto-bot to stop moving if the user-controlled bot would reach there first. I set up the Event emits from the `finish_agent` (which detected collisions with `user_robot`) but never could get the `auto-bot` to "watch" for the event from the `void entry()`. 