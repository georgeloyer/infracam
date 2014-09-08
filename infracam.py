# infracam.py
# Description
# Test programs for the infracam project
#
# History:
#   2014-09-01  gel first tests
#
# defined constants used in python wrappers of wiringPi
# INT_EDGE_SETUP    0
# INT_EDGE_FALLING  1
# INT_EDGE_RISING   2
# INT_EDGE_BOTH     3
# PUD_OFF           0
# PUD_DOWN          1
# PUD_UP            2

import wiringpi2
wiringpi2.wiringPiSetup()	# For sequential pin numbering
from array import *
import time

sequence = array('i', [262, 294, 330, 349, 392, 440, 494, 525, 0])
vbeep = [0.05, 0.05, 0.05, 0.2]
onebeep = [0.05]
twobeeps = [0.05, 0.05]

wiringpi2.pinMode(0,0)          # Pin 0 for switch, INPUT
wiringpi2.pullUpDnControl(0, 1) # set pull UP resistor for pin 0 switch
wiringpi2.pinMode(1,1)          # Pin 1 for beeper, OUTPUT
wiringpi2.softToneCreate(3)     # initialize softTone on Pin 3

def beeper(beeps):
	"Beep all of the requested beeps in the beeps list"
	for i in beeps:
		wiringpi2.digitalWrite(1,1)	# beep on
		time.sleep(i)								# length of beep from beeps list
		wiringpi2.digitalWrite(1,0)	# beep off
		time.sleep(0.025)						# interval between beeps

def gotButton():
  "Double beeps after every button press from interrupt call"
  # beeper(twobeeps)
  print("Got a button press")
  return True

# Main Program
wiringpi2.wiringPiISR(0, 2, gotButton)
k=3
while k>0 :
	for i in sequence:
		print(i)
		wiringpi2.softToneWrite(3, i)
		time.sleep(0.5)
	beeper(onebeep)
	k-=1
time.sleep(0.5)
beeper(vbeep)
