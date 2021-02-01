#!/usr/bin/env python3

import pyfirmata
import time
import sys

board = pyfirmata.Arduino(drive_port)

def drive_setup():
  board.digital[drive_port].mode = PWM
  board.digital[turn_port].mode = SERVO


# def port to send stuff to 
def board_drive_port(port):
  global board_drive_port 
  board_drive_port ="'" +  port + "'"

def drive_pin(pin):
  global drive_pin
  drive_pin = pin

def turn_pin(pin):
  global turn_pin
  turn_pin = pin


# steering
def left_max_angle(left);
  global left_max_angle
  left_max_angle = left

def right_max_angle(right):
  global right_max_angle
  right_max_angle = right

def center(cent):
  global center
  center = cent

# vars that might get redefined multiple times 
def true_speed(speed):
  global true_speed
  true_speed = speed

def motor_speed(speed):
  global motor_speed
  motor_speed = sped

def steering_angle(angle):
  global steering_angle
  steering_angle = angle 

# forward drive commands
def forward_motor_speed(speed):
  global forward_motor_speed
  forward_motor_speed = speed

def forward_center(cent):
  global forward_center
  forward_center = cent

def forward(delay):
  motor_speed = forward_motor_speed
  steering_angle = forward_center 
  board.digital[drive_pin].write(motor_speed)
  board.digital[turn_pin].write(backward_center)
  sleep(delay)

# backward drive commands 
def backward_motor_speed(speed):
  global backward_motor_speed
  backward_motor_speed = speed

def backward_center(cent):
  global center
  center = cent

def backward(delay):
  motor_speed = backward_motor_speed
  steering_angle = backward_center
  board.digital[drive_pin].write(motor_speed)
  board.digital[turn_pin].write(backward_center)
  sleep(delay)


# left drive commands
def left_motor_speed(speed):
  global right_motor_speed
  left_motor_speed = speed

def left_steering_angle(angle):
  global left_steering_angle
  left_steering_angle = angle

def left (delay)
  motor_speed = motor_speed
  steering_angle = left_max_angle
  board.digital[drive_pin].write(motor_speed)
  board.digital[turn_pin].write(left_max_angle)
  sleep(delay)

# right drive commands
def right_motor_speed(speed):
  global right_motor_speed
  right_motor_speed = speed

def right_steering_angle(angle):
  global right_steering_angle
  right_steering_angle = angle

def right (delay)
  motor_speed = right_motor_speed
  steering_angle = right_max_angle
  board.digital[drive_pin].write(motor_speed)
  board.digital[turn_pin].write(right_max_angle)
  sleep(delay)


# drive commands 
def drive(delay):
  board.digital[drive_pin].write(motor_speed)
  board.digital[turn_pin].write(right_max_angle)
  sleep(delay)

# other commands 

def delay(delay):
  sleep(delay)

