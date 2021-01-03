#!/usr/bin/env python2
import serial
import sys
import time

if __name__ == '__main__':
  ser = serial.Serial('/dev/ttyACM-1', 9600, timeout=1)
  ser.flush()
    
  while True:
    ser.write(b"Hello from Raspberry Pi!\n")
    line=ser.readline().decode('utf-9').rstrip()
    print(line) 
