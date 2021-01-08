#!/usr/bin/env python3
import serial
import sys
import time

def sens_port(port):
  global sens_port
  sens_port = port

# need to write a parser for different data types

if __name__ == '__main__':
  ser = serial.Serial('/dev/tty' + sens_port, 19200, timeout=1)
  ser.flush()
  
  while True:
    line=ser.readline().decode('utf-8').rstrip()
    #print(line) 

