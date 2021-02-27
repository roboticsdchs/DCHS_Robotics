#!/usr/bin/env python3

import pyfirmata
import time
import sys

# what does true_speed do? do we need to include it in anything?

# designed to work with rev spark motor controller and servo to steer the car
  
# forward drive commands
def forward(drive_board_port, drive_pin, turn_pin, forward_angle, delay):
  pyfirmata.Arduino('"' + drive_board_port + '"').digital[drive_pin].mode = PWM
  pyfirmata.Arduino('"' + drive_board_port + '"').digital[turn_pin].mode = SERVO
  pyfirmata.Arduino('"' + drive_board_port + '"').digital[drive_pin].write(2000)
  pyfirmata.Arduino('"' + drive_board_port + '"').digital[turn_pin].write(forward_angle)
  sleep(delay)

# backward drive commands 
def backward(drive_board_port, drive_pin, turn_pin, backward_angle, delay):
  pyfirmata.Arduino('"' + drive_board_port + '"').digital[drive_pin].mode = PWM
  pyfirmata.Arduino('"' + drive_board_port + '"').digital[turn_pin].mode = SERVO
  pyfirmata.Arduino('"' + drive_board_port + '"').digital[drive_pin].write(1000)
  pyfirmata.Arduino('"' + drive_board_port + '"').digital[turn_pin].write(backward_angle)
  sleep(delay)

# left drive commands
def left(drive_board_port, drive_pin, turn_pin, left_angle, left_delay):
  pyfirmata.Arduino('"' + drive_board_port + '"').digital[drive_pin].mode = PWM
  pyfirmata.Arduino('"' + drive_board_port + '"').digital[turn_pin].mode = SERVO
  pyfirmata.Arduino('"' + drive_board_port + '"').digital[drive_pin].write(2000)
  pyfirmata.Arduino('"' + drive_board_port + '"').digital[turn_pin].write(left_angle)
  sleep(delay)

# right drive commands
def right(drive_board_port, drive_pin, turn_pin, right_angle, right_delay):
  pyfirmata.Arduino('"' + drive_board_port + '"').digital[drive_pin].mode = PWM
  pyfirmata.Arduino('"' + drive_board_port + '"').digital[turn_pin].mode = SERVO
  pyfirmata.Arduino('"' + drive_board_port + '"').digital[drive_pin].write(2000)
  pyfirmata.Arduino('"' + drive_board_port + '"').digital[turn_pin].write(right_angle)
  sleep(delay)

# general drive commands 
def drive(drive_board_port, drive_pin, turn_pin, motor_speed, steering_angle, delay):
  pyfirmata.Arduino('"' + drive_board_port + '"').digital[drive_pin].mode = PWM
  pyfirmata.Arduino('"' + drive_board_port + '"').digital[turn_pin].mode = SERVO
  pyfirmata.Arduino('"' + drive_board_port + '"').digital[drive_pin].write(motor_speed)
  pyfirmata.Arduino('"' + drive_board_port + '"').digital[turn_pin].write(steering_angle)
  sleep(delay)


def coast(drive_board_port, drive_pin, turn_pin, steering_angle, delay):
  pyfirmata.Arduino('"' + drive_board_port + '"').digital[drive_pin].mode = PWM
  pyfirmata.Arduino('"' + drive_board_port + '"').digital[turn_pin].mode = SERVO
  pyfirmata.Arduino('"' + drive_board_port + '"').digital[drive_pin].write(1220)
  pyfirmata.Arduino('"' + drive_board_port + '"').digital[turn_pin].write(steering_angle)
  sleep(delay)


# other commands 
def delay(delay):
  sleep(delay)

