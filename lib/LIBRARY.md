# Robotics Club Library

The Robotics Club Library is designed to make the interface between the raspberry pi and the arduino as simple as possible. Through making easy to use commands to control both the sensors and movement of the car written in python. 

## Installation

### Dependencies
* [Python 3.7.9](https://www.python.org/downloads/)
* [pyFirmata 1.1.0](https://github.com/tino/pyFirmata#pyfirmata) (please contribute to the pyFirmata project as well community contribution is what makes open source great!)
* [Arduino](https://www.arduino.cc/) (supports uno but could be ported)

## Usage
#### Setting up [Firmata protocol](https://github.com/firmata/protocol) (ardunio)

1. Make sure you Arduino board is selected in "Tools" > "Port"

2. Select the StandardFirmata example from "Examples" > "Firmata" > "StandardFirmata"
  * You can learn more about Firmata [here](http://firmata.org/wiki/Main_Page)

![Alt text](https://roboticsbackend.com/wp-content/uploads/2020/01/arduino_standard_firmata_sketch.png?raw=true)

3. Upload the program to your Arduino by pressing the arrow button in the to left

4. Now remove the arduino and plug it into the computer (or pi) you are going to run the control code on

#### Setting up the python code (raspberry pi)

1. Import the library ( figure out how to do )

2. Find and define port for arduino

3. Use commands from the library to control the car ( make list of commands )

### Variables you might want to define in your program
##### DRIVE 
* board_drive_port
* drive_pin
* turn_pin
* forward_center
* backward_center
* right_max_angle
* left_max_angle
* forward_motor_speed
* backward_motor_speed
* right_motor_speed
* left_motor_speed
* right_delay
* left_delay
* true_speed

##### SENS
* units    

## TODOs
* Write tests for the lib
* Write hardware tests for the lib
* Make default definitions for all vars that can then be changed by user
* Sens_pkg
  * add support for the compass and the gps
* Drive_pkg
  * add support for the lights
  * switch to distance instead of delays (have option to use gps)
  * add software steering correction using gps and compass so the car will drive dead straight * further explore the capabilities of the rev spark
