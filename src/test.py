from gpiozero import Robot, DigitalInputDevice
from time import sleep

SAMPLETIME = 1

class Encoder(object):
    def __init__(self, pin):
        self._value = 0
        encoder = DigitalInputDevice(pin)
        encoder.when_activated = self._increment
        encoder.when_deactivated = self._increment
    def reset(self):
        self._value = 0
    def _increment(self):
        self._value += 1
@property
   def value(self):
        return self._value

r = Robot((10,9), (8,7))
e1 = Encoder(17)
e2 = Encoder(18)
m1_speed = 1.0
m2_speed = 1.0
r.value = (m1_speed, m2_speed)

while True:
    print("e1 {} e2 {}".format(e1.value, e2.value)
    sleep(SAMPLETIME)