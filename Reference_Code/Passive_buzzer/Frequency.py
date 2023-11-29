import RPi.GPI0 as GPI0
import time

buzzer = 18
GPI0.setmode(GPI0.BCM)
GPI0.setup(buzzer, GPI0.OUT)
GPI0.setwarnings(False)

pwm = GPI0.PWM(buzzzer, 262) # '262'는 음의 높이에 해당하는 특정 주파수
pwm.start(50.0)
time.sleep(1.5) # 1.5초간 음이 울리도록 시간 지연

pwm.stop()
GPI0.cleanup()
