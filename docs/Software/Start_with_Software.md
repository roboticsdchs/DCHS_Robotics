# Getting started with Software

To get a local copy or fork up and running follow these steps.

###### Don't worry about learning everything off the bat it will take some time. If you aren't interested in any of these things you can contribute to the club and this repository in other ways.

<a name="prerequisites"></a>
### Prerequisites
To be able to work on this project you will need Git, a text editor, python 3, and the Arduino ide to get the software up and running. 

1. To install Git on your system I recommend following [GitHub's guide on Installing Git](https://github.com/git-guides/install-git).

2. You will need a text editor to edit the files I prefer [Vim][Vim] but it has a large learning curve so download what ever text editor you want. Some popular options other than [Vim][Vim] are [Visual Studio Code](https://code.visualstudio.com/Download), [Notepad ++](https://notepad-plus-plus.org/downloads/), and [Sublime Text](https://www.sublimetext.com/3). There are many options, pick whatever you are the most comfortable with or whatever looks cool.

3. Next you will need python 3 the programming language that we write everything for the [Raspberry Pi][Raspberry Pi] in. You can install python 3 in a few different ways. You could use a packet manager like [asfd](https://asdf-vm.com/#/) which is my preference or with [pyenv](https://github.com/pyenv/pyenv#installation) another packet manager or directly from the [python website](https://www.python.org/downloads/).

4. Lastly you will need the Arduino IDE for programming the Arduino microcontroller. You can download the Arduino IDE from the [Arduino Website](https://www.arduino.cc/en/software).

<a name="installation"></a>
### Installation

If you are just wanting to run the code you should clone the repository. To do so I recommend following [GitHubs guide on cloning a repository](https://docs.github.com/en/free-pro-team@latest/github/creating-cloning-and-archiving-repositories/cloning-a-repository). 

If you are planning to make a pull request you will need to fork the repository. To fork a repository follow [this](https://docs.github.com/en/free-pro-team@latest/github/getting-started-with-github/fork-a-repo).

<a name="usage"></a>
### running the basic tests

You have now installed all of this stuff so how do you actually use it?

To learn how to use Git I recommend watching and reading about [The Missing Semester's](https://missing.csail.mit.edu/2020/version-control/) lecture on Git but if you don't have the patience or time you can read [this article](https://www.freecodecamp.org/news/learn-the-basics-of-git-in-under-10-minutes-da548267cc91/) and learn the basics.

Learning how to use the text editor you chose is very dependant on which one you chose. If you decided to use vim I reccomend watching and reading about [The Missing Semester's](https://missing.csail.mit.edu/2020/editors/) lecture on Vim, playing [Vim Adventures](https://vim-adventures.com), watching Vim screencasts you can find some at [Vimcasts](http://vimcasts.org), and looking at other people's vimrc's you can find many on GitHub, here is [mine](https://github.com/N1H1L0/.dotfiles/blob/main/vim/vimrc). As for the other text editors to learn the basics of Visual Studio Code look at [this](https://code.visualstudio.com/docs/getstarted/introvideos), for Notepad ++ look at [this](https://npp-user-manual.org/docs/getting-started/), for Sublime Text look at [this](https://sublime-text-unofficial-documentation.readthedocs.io/en/latest/basic_concepts.html). If you are using a different text editor or need more resources look on [Google](https://www.google.com) there are plenty of resources out there that will help you and if you are really struggling you could always ask someone else in the club.

To learn python I recommend the [Python for Everybody](https://www.coursera.org/specializations/python) course for a good basic overview. For a more advanced understanding of python I recommend really just using it in projects and looking at other people's projects on GitHub.

To learn the Arduino IDE and the Arduino language I recommend [Paul McWhorter's Arduino Lessons](https://www.youtube.com/playlist?list=PLGs0VKk2DiYx6CMdOQR_hmJ2NbB4mZQn-).

###### If you need help with any part of this feel free to ask another member of the club.

<!--
# The challenges we need to solve this year
- [ ] [Alpha - Autonomous Motion]
- [ ] [Bravo - Obstacle / Crash Avoidance]
- [ ] [Charlie - Lane Assist]
- [ ] [Delta - Parking Shark]
- [ ] [Echo - Parking Garage]
- [ ] [Foxtrot - Station Navigation]
- [ ] [Golf Task - Fleet Transport]
- [ ] [Mobility Exhibition] 
- [ ] [AIVD Cyber Security Challenge (IN DEVELOPMENT)]

create dirs for every challenge with docs for that challenge in the folder for the challenge. then link to them here.
-->
## Other Software projects
- [ ] Make a python library to control the arduino from the pi without having to know the arduino language to pass commands to the arduino.
- [ ] Figure out how to use the camera on the car for distance sensing and get rid of as many of the ultrasonic senors as possible.
- [ ] Make the headlight break light and turn signals work on every challenge.
- [ ] Write unit tests for the repo to help prevent stuff breaking.

<!-- Links -->
[Vim]: https://www.vim.org/download.php 
[Raspberry Pi]: https://www.raspberrypi.org
