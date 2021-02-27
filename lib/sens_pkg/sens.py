#!/usr/bin/env python3
import pyfirmata
import sys
import time

# formulas for ultrasonic distance measurement
#distanceCm= duration*0.034/2;
#distanceInch = duration*0.0133/2;

def ultra(sens_board_port, units, trig_pin, echo_pin, identifier):
  pyfirmata.Arduino('"' + sens_board_port + '"').digital[trig_pin].mode = OUTPUT
  pyfirmata.Arduino('"' + sens_board_port + '"').digital[echo_pin].mode = INPUT 
  while True:
    pyfirmata.Arduino('"' + sens_board_port + '"').digital[trig + trig_pin].write(0)
    sleep(0.001)
    pyfirmata.Arduino('"' + sens_board_port + '"').digital[trig + trig_pin].write(1)
    sleep(0.001)
    pyfirmata.Arduino('"' + sens_board_port + '"').digital[trig + trig_pin].write(0)
    # fix for no support for pulseIn
    while pyfirmata.Arduino('"' + sens_board_port + '"').digital[echo + echo_pin].write(0)
      pass
      start = time.time()
    while pyfirmata.Arduino('"' + sens_board_port + '"').digital[echo + echo_pin].write(1)
      pass
      end = time.time()
    if(units == metric):
      global ultra + identifier + _dist = (end - start)*0.034/2 + "cm"
    else:
      global ultra + identifier + _dist = (end - start)*0.01330/2 + "in"
    sleep(0.01)

