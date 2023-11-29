import RPi.GPIO as GPIO
import time

buzzer = 18
GPIO.setmode(GPIO. BCM) 
GPIO.setup(buzzer, GPIO.OUT) 
GPIO.setwarnings(False)

pwm = GPIO.PWM(buzzer, 1.0) # 초기 주파수 설정을 1HZ로 함.
pwm.start(50.0)

for cnt in range(0,3):
  pwm.ChangeFrequency(262) # 262는 4옥타브의 '도'에 해당되는 주파수
  time.sleep (1.0)
  pwm.ChangeFrequency(294) # 294는 4옥타브의 '레'에 해당되는 주파수
  time.sleep (1.0)
  pwm.ChangeFrequency(330)# 330은 4옥타브의 '미'에 해당되는 주파수
  time.sleep(1.0)

pwm.ChangeDutyCycle(0.0)

pwm.stop()
GPIO.cleanup()
