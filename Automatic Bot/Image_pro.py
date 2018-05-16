# python ball_tracking.py --video ball.mp4


from collections import deque
import numpy as np
import argparse
import imutils
import cv2

'''
ap = argparse.ArgumentParser()
ap.add_argument("-v", "--video",
	help="path to the (optional) video file")
ap.add_argument("-b", "--buffer", type=int, default=64,
	help="max buffer size")
args = vars(ap.parse_args())
'''

# yellow
# pixel:  [ 20 155 112]
# upper:  [ 30 165 152]
# lower:  [ 10 145  72]

# white
# pixel:  [170  29 131]
# upper:  [180  39 171]
# lower:  [160  19  91]
import serial
import numpy as np
from nanpy import Arduino
from nanpy import serial_manager

from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2


serial_manager.connect('/dev/ttyACM0')	# serial connection to Arduino


## Image Processing
# initialize the camera and grab a reference to the raw camera capture
camera = PiCamera()
camera.resolution = (640, 480)
camera.framerate = 32
rawCapture = PiRGBArray(camera, size=(640, 480))

# allow the camera to warmup
time.sleep(0.1)

arduinoSerialData = serial.Serial('/dev/ttyACM0',9600)

Lower = (10, 80,80 )
Upper = (50, 255, 255)
'''
pts = deque(maxlen=args["buffer"])

if not args.get("video", False):
	camera = cv2.VideoCapture(1)
else:
	camera = cv2.VideoCapture(args["video"])
'''


# while True:
# capture frames from the camera
for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
	
	# (grabbed, frame) = camera.read()
	# if args.get("video") and not grabbed:
	# 	break

	image = frame.array

	frame = imutils.resize(image, width=600)
	hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
	# cv2.imshow("hsv",hsv)

	mask = cv2.inRange(hsv, Lower, Upper)
	mask = cv2.erode(mask, None, iterations=2)
	mask = cv2.dilate(mask, None, iterations=2)
	# cv2.imshow("mask",mask)

	cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
		cv2.CHAIN_APPROX_SIMPLE)[-2]
	

	if len(cnts) > 0:
		c = max(cnts, key=cv2.contourArea)
		d=cv2.contourArea(c)
		# print(d)
		for e in cnts:
			cv2.drawContours(frame, [e], -1, (0, 255, 0), 2)
		((x, y), radius) = cv2.minEnclosingCircle(c)
		M = cv2.moments(c)
		center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))

		if radius > 10:
			cv2.circle(frame, (int(x), int(y)), int(radius),
				(0, 255, 255), 2)
			cv2.circle(frame, center, 5, (0, 0, 255), -1)

	pts.appendleft(center)

	for i in range(1, len(pts)):
		if pts[i - 1] is None or pts[i] is None:
			continue

		thickness = int(np.sqrt(args["buffer"] / float(i + 1)) * 2.5)
		cv2.line(frame, pts[i - 1], pts[i], (0,255 , 0), thickness)
	# leng=len(pts)
	# leng=pts[leng-1]
	print(center)
		

	# cv2.imshow("Frame", frame)
	
	frame = cv2.GaussianBlur(frame, (3, 3), 0)
	hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

	# define range of blue color in HSV
	lower_blue = np.array([160,70,70])
	upper_blue = np.array([180,255,255])
	# Threshold the HSV image to get only blue colors
	mask = cv2.inRange(hsv, lower_blue, upper_blue)


	# Bitwise-AND mask and original image
	res = cv2.bitwise_and(frame,frame, mask= mask)
	# kernel = np.ones((3,3),np.uint8)
	# res = cv2.erode(res, kernel, iterations=1)
	res = cv2.dilate(res, None, iterations=2)
	res=cv2.cvtColor(res,cv2.COLOR_BGR2GRAY)
	# print(res.shape)
	if len(l_x)<5:
		circles = cv2.HoughCircles(res, cv2.HOUGH_GRADIENT, 2.3, 50)#,param1=None,param2=None,minRadius=0,maxRadius=0)

	# ensure at least some circles were found
		if circles is not None:
		# convert the (x, y) coordinates and radius of the circles to integers
			circles = np.round(circles[0, :]).astype("int")
			p=len(circles)	
			sx,sy,sz=0,0,0
			# loop over the (x, y) coordinates and radius of the circles
			for (x, y, r) in circles:
				sx+=x
				sy+=y
				sz+=r
			x=(int)(sx/p)
			y=(int)(sy/p)
			r=(int)(sz/p)
			# draw the circle in the output image, then draw a rectangle
			# corresponding to the center of the circle
			if (len(l_x)<5):
				l_x.append(x)
				l_y.append(y)
				l_r.append(r)
			
			
			cv2.circle(frame, (x, y), r, (0, 255, 0), 4)
			cv2.rectangle(frame, (x - 5, y - 5), (x + 5, y + 5), (0, 128, 255), -1)

		# res = cv2.Canny(res,100,200)
	else:
		avg_x = (int)(sum(l_x) / 5)
		avg_y = (int)(sum(l_y) / 5)
		avg_r = (int)(min(l_r) )
		cv2.circle(frame, (avg_x, avg_y), avg_r, (0, 255, 0), 4)
		cv2.rectangle(frame, (avg_x - 5, avg_y - 5), (avg_x + 5, avg_y + 5), (0, 128, 255), -1)
		d_x=abs(center[0]-avg_x)
		d_y=abs(center[1]-avg_y)
		dist=int((d_x**2 + d_y**2)**(0.5))
		if dist<(avg_r-20):
			# ball goes in the ring
			cv2.circle(frame, (100, 100), 30, (0, 255, 0), -1)
			arduinoSerialData.write('1')
		else:
			cv2.circle(frame, (100, 100), 30, (0, 0, 255), -1)	
			arduinoSerialData.write('0')





	# cv2.imshow("img1",res)	

	# cv2.imshow('frame',frame)
	# cv2.imshow('mask',mask)
	
	rawCapture.truncate(0)


	# cv2.imshow('res',res)
	key = cv2.waitKey(1) & 0xFF

	if key == ord("q"):
		break

camera.release()
cv2.destroyAllWindows()
