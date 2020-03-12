Software Engineering for Embedded Applications
===

Winter 2020 - Final Project EEP520
---

In this repository I present the completed final project for the EEP520 course taken at the University of Washington. The full project installation, usage, capabilities, code and simulation are discussed further down in this file. Simply, the project completed is a maze with two built-in robots. One autonomously drives itself through the maze and the other can be manually controlled by the user to get to a common final destination. A visual representation of the simulation can be found in the `Image` folder located in this directory. I decided to name this project: `Mazed`. 

Installation
---

`Mazed ` runs solely due to the help of two packages built by the course Instructor called ELMA and ENVIRO. To run this project you will need to call these packages; click [here](https://github.com/klavinslab/elma) and [here](https://github.com/klavinslab/enviro) for more information on ELMA and ENVIRO respectively. The instructor made these packages available through [Docker](https://www.docker.com) which I recommend installing to virtually access these packages. Once Docker or these packages have been installed in your computer, simply download this repository to your computer and open with the IDE of preference.

Usage
---

To run ELMA/ENVIRO's enviroment, move in the terminal to the directory where this entire repository is located at and run:<br />
```bash
docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.2 bash
```
For this project, I used ENVIRO's version 1.2 but you may find information on other versions in the ENVIRO's repo. Once this command is entered, you should now be operating within a Docker container using ELMA/ENVIRO. At this point, from within the main directory, simply enter: `esm start`. This will start broadcasting to a localhost channel. In a web-browser enter:   `localhost`. At this point you should see in localhost that the "server" is not running, this is because the simulation has not been started yet. To start it simply enter in the terminal: `enviro`, and this should immediately display the simulation of `Mazed`. <br />

To control the manual robot, use keys "t" for up, "v" for down, "f" for left, and "h" for right. You can shutdown the simulation at anytime by simply using `CTRL + c`. To restart the simulation re-enter `enviro`. 

Visuals
---

For a visual representation of what you should be seeing when running the simulation, simply enter the `Images` folder in this directory. 

License
---

This repository contains open-source code which is governed by the MIT license. 