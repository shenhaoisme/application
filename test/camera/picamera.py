#! /usr/bin/python

from picamera import picamera
from time import sleep

camera = picamera()

camera.start_preview()
sleep(10)
camera.stop_preview()
