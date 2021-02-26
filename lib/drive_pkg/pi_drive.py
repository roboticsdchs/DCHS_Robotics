#!/usr/bin/env python3

import pyfirmata
import time
import sys

#what does true_speed do? do we need to include it in anything?

# setup for pyFirmata
def board_drive_setup(board_drive_port):
  global board_drive = pyfirmata.Arduino("'" + drive_board_port + "'")
  
# forward drive commands
def forward(drive_pin, turn_pin, forward_motor_speed, forward_center, delay):
  board_drive.digital[drive_pin].mode = PWM
  board_drive.digital[turn_pin].mode = SERVO
  board_drive.digital[drive_pin].write(forward_motor_speed)
  board_drive.digital[turn_pin].write(backward_center)
  sleep(delay)

# backward drive commands 
def backward(drive_pin, turn_pin, backward_motor_speed, backward_center, delay):
  board_drive.digital[drive_pin].mode = PWM
  board_drive.digital[turn_pin].mode = SERVO
  board_drive.digital[drive_pin].write(backward_motor_speed)
  board_drive.digital[turn_pin].write(backward_center)
  sleep(delay)

# left drive commands
def left(drive_pin, turn_pin, left_motor_speed, left_max_angle, left_delay):
  board_drive.digital[drive_pin].mode = PWM
  board_drive.digital[turn_pin].mode = SERVO
  board_drive.digital[drive_pin].write(left_motor_speed)
  board_drive.digital[turn_pin].write(left_max_angle)
  sleep(delay)

# right drive commands
def right(drive_pin, turn_pin, right_motor_speed, right_turn_angle, right_delay):
  board_drive.digital[drive_pin].mode = PWM
  board_drive.digital[turn_pin].mode = SERVO
  board_drive.digital[drive_pin].write(right_motor_speed)
  board_drive.digital[turn_pin].write(right_turn_angle)
  sleep(delay)

# general drive commands 
def drive(drive_pin, turn_pin, motor_speed, steering_angle, delay):
  board_drive.digital[drive_pin].mode = PWM
  board_drive.digital[turn_pin].mode = SERVO
  board_drive.digital[drive_pin].write(motor_speed)
  board_drive.digital[turn_pin].write(steering_angle)
  sleep(delay)

# other commands 
def delay(delay):
  sleep(delay)

