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

Visuals
---

For a visual representation of what you should be seeing when running the simulation, simply enter the `Images` folder in this directory. 

License
---

This repository contains open-source code which is governed by the MIT license. 