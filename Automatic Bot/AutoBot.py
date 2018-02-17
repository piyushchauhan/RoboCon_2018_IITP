#!/usr/bin/env python
# import the necessary packages
import serial
import numpy as np
from nanpy import Arduino
from nanpy import serial_manager

from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2


serial_manager.connect('/dev/ttyACM0')    	 # serial connection to Arduino
# Line Following and register locations from arduino


## Image Processing
# initialize the camera and grab a reference to the raw camera capture
camera = PiCamera()
camera.resolution = (640, 480)
camera.framerate = 32
rawCapture = PiRGBArray(camera, size=(640, 480))

# allow the camera to warmup
time.sleep(0.1)

# capture frames from the camera
for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
	# grab the raw NumPy array representing the image, then initialize the timestamp
	# and occupied/unoccupied text
	image = frame.array

	# show the frame
	cv2.imshow("Frame", image)
	key = cv2.waitKey(1) & 0xFF

	# clear the stream in preparation for the next frame
	rawCapture.truncate(0)

	# if the `q` key was pressed, break from the loop
	if key == ord("q"):
		break