#!/usr/bin/env python3
import pyfirmata
import sys
import time


# add support for both metric and imperial 
# add compass and gps 

def units(system):
  global units
  units = system

board = pyfirmata.Arudino(sens_port)

def sens_port(port):
  global sens_port
  sens_port ="'" + port "'"

def sens_setup():
  board.digital[trig1].mode = OUTPUT
  board.digital[echo1].mode = INPUT
  board.digital[trig2].mode = OUTPUT
  board.digital[echo2].mode = INPUT
  board.digital[trig3].mode = OUTPUT
  board.digital[echo3].mode = INPUT


def trig1(pin):
  global trig1
  trig1 = pin

def echo1(pin):
  global  echo1 
  echo1 = pin

def trig2(pin):
  global  trig2
  trig2 = pin

def echo2(pin):
  global  echo2
  echo2 = pin

def trig3(pin):
  global trig3
  trig3 = pin

def echo3(pin):
  global echo3
  echo3 = pin

#formulas
#distanceCm= duration*0.034/2;
#distanceInch = duration*0.0133/2;
  
def ultra(num):
  while True:
    board.digital[trig + num].write(0)
    sleep(0.001)
    board.digital[trig + num].write(1)
    sleep(0.001)
    board.digital[trig + num].write(0)
    # fix for no support for pulseIn
    while board.digital[echo + num].write(0)
      pass
      start = time.time()
    while board.digital[echo + num].write(1)
      pass
      end = time.time()
    if(units == metric):
      ultra + num + _dist = (end - start)*0.034/2
    else:
      ultra + num + _dist = (end - start)*0.01330/2
    sleep(0.01)

