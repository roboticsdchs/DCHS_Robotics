# The Xbox Car

## Driving the xbox car

To drive the xbox car simply turn on the car and turn the Xbox 360 controller on. Right trigger is forward, left trigger is backward, and the left stick controlls the steering .

## About the code

The code for the xbox car is really just using the [XBOXRECV library](https://github.com/felis/USB_Host_Shield_2.0/blob/master/XBOXRECV.cpp) which is part of the [USB Host Library Rev. 2.0](https://github.com/felis/USB_Host_Shield_2.0) to wirelessly get the inputs of the Xbox 360 controller and translate them to drive and turning commands. 

## About the hardware 

The hardware for having an Xbox car that is different than the sensorless car is the additon of the USB Host Shield which the hardware manual can be accessed [here](https://chome.nerpa.tech/usb-host-shield-hardware-manual/), the Xbox 360 Wireless Receiver, and a Xbox 360 controller.

###### A note about pins

Some pins are reserved for the USB Host Shield to communicate with the Arduino. Attempted usage of those pins for other purposes such as drive or turn control will result in the Xbox 360 controller not pairing with the Xbox 360 Wireless Receiver. For the red car we used pins 5 and 6 for drive and turn control without issue.