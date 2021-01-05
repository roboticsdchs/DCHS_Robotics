# Getting started with Hardware

###### Don't worry about learning everything off the bat it will take some time. If you aren't interested in any of these things you can contribute to the club and this repository in other ways.

## Hardware Systems

<!-- someone make a wiring diagram of the car and for each subsection highlight the part of the car we are describing -->

### Power Path 

<!--draw path of power throughout the car -->

### MicroControllers

There are going to be multiple microcontroller on the car when we transition to using the [Raspberry Pi][Raspberry Pi] as a main brain for all of the control on the car. Plugged into the Raspberry Pi will most likely be one arduino with the gps module, compass, and ultrasonics senors plugged into it sending all of the senor data back to the Raspberry Pi. Then there will be an arduino with the steering servo, drive motors, and lights plugged into it. That arduino will be responsible for the output of control signals to the car. The Raspberry Pi will also probably have a webcam plugged into it.

<!-- someone make a diagram of micro controller and arduino layout -->

### Drive motors

The two large motors at the back of the car are the drive motors. They will be controlled by the arduino that is responsible for controlling the car. These motors car the factory dc motors that came with the power wheels and are controlled by the spark motor controller that is taking in a 5v signal for the arduino responsible for controlling the car. The spark motor controller take the 5v from the arduino and makes it into 12v power for the drive motors. 

<!-- diagram of Pi to arduino to spark motor controller to drive motors -->

### Steering

On the underside of the car there is a servo mounted that connects to the steering rack that controls the angle of the front wheels of the car. This servo is controlled by the arduino that is responsible for controlling the car which is ultimately controlled by the Raspberry Pi. This steering setup has a pretty good steering lock angle but the motor is slightly underpowered so you have to be moving a little bit to be able to turn and the car doesn't drive dead straight which is most likely caused by the wheels and could be software corrected but in future versions it would be nice to avoid this problem.

<!-- diagram of pi to arduino to servo-->
<!-- diagram of the steering system-->
### Sensors 

There are many sensors on the car that will be plugged into an arduino that is streaming the data back to the Raspberry Pi.

#### Positioning Sensors

There GPS shield which directly attaches to the top of the arduino and produces the GPS coordinates for where the car is.

There is a compass and gyroscope senor on the front of the car plugged in to the senor arduino  that tells you where the car is pointing which is very useful when stating in the direction for the destination because you know the orientation of the car and don't have to drive around in circles to find it using the GPS.

<!-- diagram of where they are and their wiring -->
#### Distance sensors 

Currently there are 3 ultrasonic sensors on the car. 

There is the one in the front that will e plugged into the sensor arduino. 
There is the one on the starboard of the car that will be plugged into the sensor arduino.
Lastly there is the one on the back of the car that will by plugged into the sensor arduino as will.

[Here](https://www.youtube.com/watch?v=1jGvzNrtF24) is a video explaining how an Ultrasonic Sensor works.

<!-- diagram of where it is and the wiring -->

#### Camera

There will most likely be a webcam mounted on the bask on a servo that swivels so that we can see as much of the road and the surrounding as possible also allowing us to turn the camera for crash advoidance while turning and the option of using it in parking.

The webcam will plug directly into the Raspberry pi.

<!-- diagram of camera position, servo underneath it, and wiring -->

### Lights

On the car there are 2 lights one in the front that acts and a headlight and one in the back that acts as a break light and turn signals. 

The light are controlled by the arduino that is responsible for car control that is being controlled by the Raspberry Pi.

<!-- diagram on the location of the light and their wiring -->

# Hardware projects

- [ ] Create docs on how to and the standards of working on the car.
- [ ] Make a wiring diagram of the car.
- [ ] Make nice encloses for the lights on the car.
- [ ] Hide the cables and microprocessors.
- [ ] Make the steering run true without software correction.
- [ ] Make interchangeable slot things for the different sized ultrasonic sensors.
- [ ] Make a drive up battery charger for the car so you can drive it to and from the charger remotely.

## CAD

What is CAD. CAD stands for Cardboard Aided Design. Jokes aside CAD is Computer Aided Design meaning that it is software that assists you in designing things on the computer.

### 2d design 

In our club 2d design is mostly used for designing and making laser cut parts.

#### Software for 2d design 

For 2d design there are a few options that you can use to design things one of the most popular options is [Adobe Photoshop](https://www.adobe.com/products/photoshop.html), a popular open source alternative to Photoshop is [Inkscape](https://inkscape.org), and you could also use [FUSION 360][FUSION 360].

#### Using 2d design software

To learn how to use 2d design software. To learn Photoshop you can follow [this](https://www.oberlo.com/blog/how-to-use-photoshop) tutoral. To learn how to use Inkscape [here](https://inkscape.org/learn/). Learn to use FUSION 360 for lasercutting [here](https://core-electronics.com.au/tutorials/making-boxes-with-fusion-360-for-laser-cutting-tutorial.html).  

### 3d design

In out club 3d design is mostly used for designing and making 3d printed parts.

#### Software for 3d design

For 3d CAD design there are a multitude of options you can chooses from one of the easiest and best being [TINKERCAD](https://www.tinkercad.com). Another good option for 3d CAD design is [FUSION 360][FUSION 360] which is very powerful but not as intuitive. 

#### Using 3d CAD software

To learn to use 3d CAD software can be very challenging some good resources to checkout to get started are [this](https://www.tinkercad.com/learn/designs) for learning TINKERCAD and [this](https://www.youtube.com/playlist?list=PLznyNXKQaKuetAIXhN-ihc1uhxti-oayo) for learning FUSION 360.

<a name="prerequisites"></a>
### Prerequisites to run basic tests

To run the basic tests which you will probally want to do at some point you will want Git, a text editor, python 3, and the Arduino ide to get the basic tests up and running but it isn't completely necessary so if you have no interest in running the basic steps you a skip this step. 


1. To install Git on your system I recommend following [GitHub's guide on Installing Git](https://github.com/git-guides/install-git).

2. You will need a text editor to edit the files I prefer [Vim][Vim] but it has a large learning curve so download what ever text editor you want. Some popular options other than [Vim][Vim] are [Visual Studio Code](https://code.visualstudio.com/Download), [Notepad ++](https://notepad-plus-plus.org/downloads/), and [Sublime Text](https://www.sublimetext.com/3). There are many options, pick whatever you are the most comfortable with or whatever looks cool. A text editor is optional for running the basic tests but it is necessary if you want to create or modify any files.

3. Next you will need python 3 the programming language that we write everything for the [Raspberry Pi][Raspberry Pi] in. You can install python 3 in a few different ways. You could use a packet manager like [asfd](https://asdf-vm.com/#/) which is my preference or with [pyenv](https://github.com/pyenv/pyenv#installation) another packet manager or directly from the [python website](https://www.python.org/downloads/).

4. Lastly you will need the Arduino IDE for programming the Arduino microcontroller. You can download the Arduino IDE from the [Arduino Website](https://www.arduino.cc/en/software).

<a name="installation"></a>
### Installation

If you are just wanting to run the code you should clone the repository. To do so I recommend following [GitHubs guide on cloning a repository](https://docs.github.com/en/free-pro-team@latest/github/creating-cloning-and-archiving-repositories/cloning-a-repository). 

If you are planning to make a pull request you will need to fork the repository. To fork a repository follow [this](https://docs.github.com/en/free-pro-team@latest/github/getting-started-with-github/fork-a-repo).

### Running the Basic tests

To run the basics tests for the arduino simply follow [this](https://www.arduino.cc/en/main/howto)

To run the basics tests for the raspberry pi (python) follow [this](https://realpython.com/run-python-scripts/)

<a name="usage"></a>
### Learning the Basics

If you want to learn how to write the basic tests or just gain a deeper understanding of how they work:

To learn how to use Git I recommend watching and reading about [The Missing Semester's](https://missing.csail.mit.edu/2020/version-control/) lecture on Git but if you don't have the patience or time you can read [this article](https://www.freecodecamp.org/news/learn-the-basics-of-git-in-under-10-minutes-da548267cc91/) and learn the basics.

Learning how to use the text editor you chose is very dependiant on which one you chose. If you decided to use vim I reccomend watching and reading about [The Missing Semester's](https://missing.csail.mit.edu/2020/editors/) lecture on Vim, playing [Vim Adventures](https://vim-adventures.com), watching Vim screencasts you can find some at [Vimcasts](http://vimcasts.org), and looking at other people's vimrc's you can find many on GitHub, here is [mine](https://github.com/N1H1L0/.dotfiles/blob/main/vim/vimrc). As for the other text editors to learn the basics of Visual Studio Code look at [this](https://code.visualstudio.com/docs/getstarted/introvideos), for Notepad ++ look at [this](https://npp-user-manual.org/docs/getting-started/), for Sublime Text look at [this](https://sublime-text-unofficial-documentation.readthedocs.io/en/latest/basic_concepts.html). If you are using a different text editor or need more resources look on [Google](https://www.google.com) there are plenty of resources out there that will help you and if you are really struggling you could always ask someone else in the club.

To learn python I recommend the [Python for Everybody](https://www.coursera.org/specializations/python) course for a good basic overview. For a more advanced understanding of python I recommend really just using it in projects and looking at other people's projects on GitHub.

To learn the Arduino IDE and the Arduino language I recommend [Paul McWhorter's Arudino Lessons](https://www.youtube.com/playlist?list=PLGs0VKk2DiYx6CMdOQR_hmJ2NbB4mZQn-).

###### If you need help with any part of this feel free to ask another member of the club.

<!-- LINKS -->
[FUSION 360]: https://www.autodesk.com/products/fusion-360/overview
[Vim]: https://www.vim.org/download.php 
[Raspberry Pi]: https://www.raspberrypi.org
