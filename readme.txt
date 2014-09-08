WiringPi is a GPIO access library written in C for the BCM2835 used in the Raspberry Pi. It’s released under the GNU LGPLv3 license and is usable from C and C++ and many other languages with suitable wrappers (See below) It’s designed to be familiar to people who have used the Arduino “wiring” system1

The Raspberry Pi has a 26-pin General Purpose Input/Output (GPIO) connector and this carries a set of signals and buses. There are 8 general purpose digital I/O pins – these can be programmed as either digital outputs or inputs. One of these pins can be designated for PWM output too. Additionally there is a 2-wire I2C interface and a 4-wire SPI interface (with a 2nd select line, making it 5 pins in total) and the serial UART with a further 2 pins.

The Revision 2 Raspberry Pi has an additional 4 GPIO lines on a separate connector which you have to solder onto the board.
The model B+ Raspberry Pi represents 2 years of research, development and testing and now features a single 40-pin GPIO connector with 28 usable GPIO pins.
The I2C, SPI and UART interfaces can also be used as general purpose I/O pins when not being used in their bus modes, giving a grand total of 8 + 2 + 5 + 2 = 17 I/O pins on the P1 connector (plus 4 more on the P5 connector on a Revision 2 Pi)

WiringPi includes a command-line utility gpio which can be used to program and setup the GPIO pins. You can use this to read and write the pins and even use it to control them from shell scripts.



WiringPi2-Python

git clone https://github.com/Gadgetoid/WiringPi2-Python.git
sudo apt-get install python-dev
sudo apt-get install python-setuptools
sudo python setup.py install

import wiringpi2
wiringpi2.wiringPiSetup()   # for sequential pin numbering
wiringpi2.pinMode(pin, mode) # mode: 1=OUTPUT, 0=INPUT
wiringpi2.softToneCreate(pin)
wiringpi2.softToneWrite(pin, freq) # freq=Hz


infracam.py is aimed at dedicating a RaspberryPi to imaging, both visible light and infrared imaging using both the PiNoir camera and the infragram camera from PublicLab. Only one of the PiNoir and Raspicam cameras can be connected at once,so it's a manual process to switch between them.  The projects I want to use these for don't require a quick switch, so that should be OK.

Projects:
  1. take snapshots of vegetation and use the infragram process to create false color images that demonstrate where in a plant photosynthesis is occurring most strongly.

  2. take time lapse photographs of the garden to detect pests that are visiting the garden and eating our veggies.  This requires an infrared light source to illuminate the subject.  So far this does not include a motion sensor function, but could be added later.

User scenario:
1. Power up the camera. Get three short beeps to indicate the camera is ready for use and is in snapshot mode initially.
2. Press the button once to take a snapshot. Audible beep to indicate a snapshot has been taken and stored on local disk. 
3. Uploads snapshots in the background to dropbox folder if there is network connectivity.
4. Double press the button to enter sequence mode. Camera emits one long and two short beeps to indicate it is ready to begin a sequence.
5. User double presses the button to exit sequence mode. Camera emits three short beeps to indicate it is ready for use in snapshot mode.
6. User presses button once to begin sequence. All sequence parameters are set in a configuration file that is read once on reboot - can't change any of those parameters in this implementation except through the config file.  Camera emits a single beep with each image taken. It creates a folder with the starting date and time encoded in the name and adds the images as jpg files to that folder.
7. Uploads the new folder name and the images to drop box in the background if there is network connectivity.

Python wrapper on wiringpi2 has a killer bug with interrupt handling - moving on to c

