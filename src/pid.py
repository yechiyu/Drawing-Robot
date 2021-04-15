import threading
import numpy
from gpiozero import DigitalInputDevice, Robot,OutputDevice
from time import sleep

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

def clamp(value):
    return max(min(1, value), 0)
    
enable1=OutputDevice(26)
enable1.on()
enable2=OutputDevice(12)
enable2.on()
SAMPLETIME = 0.1
TARGET = 15
KP = 0.18
KD = 0.00
KI = 0.01

r = Robot((20,21), (6,13)) 
e1 = Encoder(17)
e2 = Encoder(18)
e1 = Encoder(17)
e2 = Encoder(18)


m1_speed = -0.1
m2_speed = 0.1
r.value = (m1_speed, m2_speed)

e1_prev_error = 0
e2_prev_error = 0

e1_sum_error = 0
e2_sum_error = 0

while True:

    e1_error = TARGET - e1.value
    e2_error = TARGET - e2.value

    m1_speed += (e1_error * KP) + (e1_prev_error * KD) + (e1_sum_error * KI)
    m2_speed += (e2_error * KP)  + (e1_prev_error * KD) + (e2_sum_error * KI)

    m1_speed = max(min(1, m1_speed), 0)
    m2_speed = max(min(1, m2_speed), 0)
    r.value = (m1_speed, m2_speed)

    print("e1 {} e2 {}".format(e1.value, e2.value))
    print("m1 {} m2 {}".format(m1_speed, m2_speed))

    e1.reset()
    e2.reset()

    sleep(SAMPLETIME)

    e1_prev_error = e1_error
    e2_prev_error = e2_error

    e1_sum_error += e1_error
    e2_sum_error += e2_error

print(numpy.zeros(3,1))