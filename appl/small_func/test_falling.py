#!/usr/bin/python

import RPi.GPIO as GPIO
import time
from threading import Timer

switchcount=0

def test_fun(channel):
	print('the function is run')
#GPIO setup board type
GPIO.setmode(GPIO.BCM)
#setup GPIO input and pullup
GPIO.setup(26, GPIO.IN, pull_up_down=GPIO.PUD_UP)

#setup GPIO falling 
GPIO.add_event_detect(26, GPIO.FALLING,callback=test_fun, bouncetime=10)
print('run?')
while switchcount < 10:
	if  GPIO.event_detected(26):
		switchcount += 1
GPIO.remove_event_detect(26)
