import cv2
import numpy as np
import sys

camera_port = 0
camera = cv2.VideoCapture(camera_port)
image_hsv=None
pixel=(20,60,80)
while(True):
    # Capture frame-by-frame
    ret, img = camera.read()
    cv2.imshow('T3',img)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
def get_image():
    retval, im = camera.read()
    return im
def pick_color(event,x,y,flags,param):
    if event == cv2.EVENT_LBUTTONDOWN:
        pixel=image_hsv[y,x]
        upper = np.array([pixel[0]+10,pixel[1]+10,pixel[2]+40])
        lower = np.array([pixel[0]-10,pixel[1]-10,pixel[2]-40])
        print("pixel: ",pixel)
        print("upper: ",upper)
        print("lower: ",lower)
        image_mask = cv2.inRange(image_hsv,lower,upper)
        cv2.imshow("mask",image_mask)


image_src = get_image();

if image_src is None:
    print ("the image read is none")
else:
    cv2.imshow("bgr",image_src)
    cv2.namedWindow('hsv')
    cv2.setMouseCallback('hsv',pick_color)
    image_hsv = cv2.cvtColor(image_src,cv2.COLOR_BGR2HSV)
    cv2.imshow("hsv",image_hsv)
cv2.waitKey(0)
cv2.destroyAllWindows()
