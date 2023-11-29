from picamera import PiCamera
from time import sleep

camera = PiCamera()

camera.start_preview()
camera.brightness = 70
sleep(5)
camera.capture('/home/pi/bright.jpg')
camera.stop_preview()
