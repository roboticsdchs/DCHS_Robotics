#!/usr/bin/env python3
import serial
import sys
import time


# need to add lights
# need to figure out how to handle the looping and setup 
# might want to transition to have a distance input for drive instead of time 
# constant definitions change so that are auto defined to something but can be overwritten in the code so you only have to change if you made mod to the car and are temporally testing them

def drive_port(port):
  global drive_port 
  drive_port = port

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

# drive commands 
def forward(delay):
  true_speed = 254
  motor_speed = 110
  steering_angle = center 
  ser.write(b"TrueSpeed = " + true_speed + "; movemotors.write(" + motor_speed +"); turnmotor.write(" + steering_angle + "); delay(" + delay + ");")

def backward(delay):
  true_speed = 127
  motor_speed = 70
  steering_angle = center
  ser.write(b"TrueSpeed = " + true_speed + "; movemotors.write(" + motor_speed +"); turnmotor.write(" + steering_angle + "); delay(" + delay + ");")

def left (delay)
  true_speed = 254
  motor_speed = 110
  steering_angle = left_max_angle
  ser.write(b"TrueSpeed = " + true_speed + "; movemotors.write(" + motor_speed +"); turnmotor.write(" + steering_angle + "); delay(" + delay + ");")

def right (delay)
  true_speed = 254
  motor_speed = 110
  steering_angle = right_max_angle
  ser.write(b"TrueSpeed = " + true_speed + "; movemotors.write(" + motor_speed +"); turnmotor.write(" + steering_angle + "); delay(" + delay + ");")

def drive(delay):
  ser.write(b"TrueSpeed = " + true_speed + "; movemotors.write(" + motor_speed +"); turnmotor.write(" + steering_angle + "); delay(" + delay + ");")

# other commands 

def delay(delay):
  ser.write(b"delay(" + delay + ");")


# put every thing in here that you want to sent to arduino
def serial_start(contents):
  if __name__ == '__main__':
    ser = serial.Serial('/dev/tty' + drive_port, 9600, timeout=1)
    ser.flush()
    
    while True:
      contents

