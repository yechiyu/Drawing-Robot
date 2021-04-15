from gpiozero import DigitalInputDevice, Robot
from time import sleep

class Encoder(object):
    def __init__(self, pin):
        self._value = 0

        # setup gpiozero to call increment on each when_activated
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

SAMPLETIME = 0.5

# r = Robot((20,21), (6,13)) 

e1 = Encoder(15)
e2 = Encoder(16)
e3 = Encoder(35)
e4 = Encoder(36)
#start the robot
# m1_speed = -0.1
# m2_speed = -0.1
# r.value = (m1_speed, m2_speed)

#find a sample rate
while True:
    print("e1 {} e2 {}".format(e1.value, e2.value))
    print("e3 {} e4 {}".format(e3.value, e4.value))
    sleep(SAMPLETIME)