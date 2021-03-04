#!/usr/bin/env python3
import pyfirmata
import sys
import time

# formulas for ultrasonic distance measurement
# cm/2.54 = in

# HC-SR04 (returns a list of [measurement, raw time stamp]
def ultra(sens_board_port, units, trig_pin, echo_pin):
  sens_board_port.set_pin_mode_sonar(trig_pin, echo_pin, callback=None, timeout=8000)
  data = sens_board_port.sonar_read(trig_pin)
  if(units == metric):
     return data
   else:
     while i < len(data):
       in_data = data[i]/2.54
         i +=  2
     return in_data
