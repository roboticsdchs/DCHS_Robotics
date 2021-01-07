#!/usr/bin/env python3
import serial
import sys
import time

if __name__ == '__main__':
  ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
  ser.flush()
  
  while True:
    ser.write(b"Hello from Raspberry Pi!\n")
    line=ser.readline().decode('utf-8').rstrip()
    print(line) 
