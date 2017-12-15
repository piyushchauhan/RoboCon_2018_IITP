import cv2
import numpy as np

"""
def create_blank(width, height, rgb_color=(255, 255, 255)):
    #Create new image(numpy array) filled with certain color in RGB
    image = np.zeros((height, width, 3), np.uint8)  # Create black blank image
    color = tuple(reversed(rgb_color))  # Since OpenCV uses BGR, convert the color first
    image[:] = color  # Fill image with color
    return image


# Create new blank 300x300 red image
width, height = 300, 300
white = (255, 255, 255)
image = create_blank(width, height, rgb_color=white)

# Creating a red filled circle at the center of the image with radii 100px
cv2.circle(image, (width // 2, height // 2), 100, (0, 0, 255), -1)
# Creating a white filled circle at the center of the image with radii 50px
cv2.circle(image, (width // 2, height // 2), 50, (255, 255, 255), -1)

new_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# Detecting circles
circles = cv2.HoughCircles(new_image, cv2.HOUGH_GRADIENT, 1, 20, param1=50, param2=30, minRadius=0, maxRadius=0)
circles = np.uint16(np.around(circles))

if circles is not None:
    for i in circles[0, :]:
        # draw the outer circle
        cv2.circle(image, (i[0], i[1]), i[2], (0, 255, 0), 2)
        # draw the center of the circle
        cv2.circle(image, (i[0], i[1]), 2, (0, 0, 255), 3)

# cv2.imshow('detected circles', new_image)
cv2.imshow('image', image)
"""

cap = cv2.VideoCapture(1)
while True:
    _, frame = cap.read()
    # modifying the frame
    grey = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    vidCircles = cv2.HoughCircles(grey, cv2.HOUGH_GRADIENT, 1, 20, param1=10, param2=1, minRadius=0, maxRadius=0)
    vidCircles = np.uint16(np.around(vidCircles))

    if vidCircles is not None:
        for i in vidCircles[0, :]:
            # draw the outer circle
            cv2.circle(frame, (i[0], i[1]), i[2], (0, 255, 0), 1)
            # draw the center of the circle
            cv2.circle(frame, (i[0], i[1]), 2, (0, 0, 255), 3)

    cv2.imshow('frame', frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
cap.release()  # camera will be released
cv2.waitKey(0)
cv2.destroyAllWindows()
