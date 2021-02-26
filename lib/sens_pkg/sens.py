#!/usr/bin/env python3
import pyfirmata
import sys
import time

#setup for pyFirmata
def board_sens_setup(board_sens_port)
  global board_sens = pyfirmata.Arudino("'" + sens_port + "'")

# formulas for ultrasonic distance measurement
#distanceCm= duration*0.034/2;
#distanceInch = duration*0.0133/2;

def ultra(units, trig_pin, echo_pin, identifier):
  board_sens.digital[trig_pin].mode = OUTPUT
  board_sens.digital[echo_pin].mode = INPUT 
  while True:
    board_sens.digital[trig + trig_pin].write(0)
    sleep(0.001)
    board_sens.digital[trig + trig_pin].write(1)
    sleep(0.001)
    board_sens.digital[trig + trig_pin].write(0)
    # fix for no support for pulseIn
    while board_sens.digital[echo + echo_pin].write(0)
      pass
      start = time.time()
    while board_sens.digital[echo + echo_pin].write(1)
      pass
      end = time.time()
    if(units == metric):
      global ultra + identifier + _dist = (end - start)*0.034/2 + "cm"
    else:
      global ultra + identifier + _dist = (end - start)*0.01330/2 + "in"
    sleep(0.01)

