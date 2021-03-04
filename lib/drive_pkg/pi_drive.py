#!/usr/bin/env python3

import time
import sys
from pymata4 import pymata4

# what does true_speed do? do we need to include it in anything?

# designed to work with rev spark motor controller and D645MW to steer the car

# switch to .writeMicroseconds so that we can use docs on rev spark

# use FirmataExpress > StandardFirmata

# motor speed is from 0-180 i think as you control the rev spark as a servo

# driving stuff

def drive(drive_board_port, drive_pin, turn_pin, motor_speed, steering_angle, delay):
  drive_board.set_pin_mode_servo(drive_pin, 1000, 2000) #https://www.revrobotics.com/content/docs/REV-11-1200-UM.pdf
  drive_board.servo_write(drive_pin, motor_speed)
  drive_board.set_pin_mode_servo(turn_pin, 750, 2250) #https://www.servocity.com/d645mw-servo/
  drive_board.servo_write(steering_angle)
  time.sleep(delay)
 
def forward(drive_board_port, drive_pin, turn_pin, delay):
  drive_board.set_pin_mode_servo(drive,pin, 100, 2000)
  drive_board.servo_write(drive_pin, 180)
  drive_board.servo_pin_mode_servo(turn_pin, 750, 2250)
  drive_board.servo_write(90)
  time.sleep(delay)

def backward(drive_board_port, drive_pin, turn_pin, backward_angle, delay):
  drive_board.set_pin_mode_servo(drive,pin, 100, 2000)
  drive_board.servo_write(drive_pin, 0)
  drive_board.servo_pin_mode_servo(turn_pin, 750, 2250)
  drive_board.servo_write(90)
  time.sleep(delay)

def left(drive_board_port, drive_pin, turn_pin, left_angle, left_delay):
  drive_board.set_pin_mode_servo(drive,pin, 100, 2000)
  drive_board.servo_write(drive_pin, 180)
  drive_board.servo_pin_mode_servo(turn_pin, 750, 2250)
  drive_board.servo_write(45)
  time.sleep(delay)

def right(drive_board_port, drive_pin, turn_pin, right_angle, right_delay):
  drive_board.set_pin_mode_servo(drive,pin, 100, 2000)
  drive_board.servo_write(drive_pin, 180)
  drive_board.servo_pin_mode_servo(turn_pin, 750, 2250)
  drive_board.servo_write(135)
  time.sleep(delay)

def coast(drive_board_port, drive_pin, turn_pin, steering_angle, delay):
  drive_board.set_pin_mode_servo(drive,pin, 100, 2000)
  drive_board.servo_write(drive_pin, 90)
  drive_board.servo_pin_mode_servo(turn_pin, 750, 2250)
  drive_board.servo_write(135)
  time.sleep(delay)

# other commands 
def delay(delay):
  time.sleep(delay)
 
