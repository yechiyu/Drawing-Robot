## https://github.com/yechiyu/Drawing-RobotDRAWING ROBOT

In this project, we build a robot that extracts line traces from an image and
program it to reproduce and duplicate the images as a drawing on a whiteboard.
our robot acquires an image (or load an existing image), extract the line traces
from that image, scale the drawing to the drawable area of your whiteboard, and
then reproduce the drawing by moving a marker along the same set of paths. Along
the way, we use motor drive theory, PID closed-loop control, Image processing,
track planning, pixel value and physical distance conversion, math computation,
trigonometry and C++ multithreading.

### *1.0 Robot hardware control*

### *Driving DC Motors*

When controlling a motor from a single chip computer, we avoid connecting the
output pin of the single chip computer directly to the motor terminal, because
the current demand of the motor can damage the chip. In addition, most motors
require a higher voltage than the microcontroller can provide. To control a DC
motor from a microcontroller without damaging the microcontroller, we used a DC
motor driver that was compatible with the Raspberry Pi.

![](media/0c79e5b0928a2b11476ba8cb85963dce.png)

**What's on Board:**

Raspberry Pi GPIO interface: for connecting Raspberry Pi

Motor screw terminal: for connecting motors

External power input

74LVC4245AD: voltage level conversion chip, buffer device

MC33886: motor driver chip

LM2596-5.0: 5V regulator

Power indicator

Raspberry Pi power selection

OFF: Raspberry Pi powers the Motor Driver Board

ON: Motor Driver Board powers the Raspberry Pi

2A self-recovery fuse

IR receiver

Schottky diodes: protects the motor driver

Power supply anti-reverse diode

The H-Bridge

An H-Bridge is an electronic circuit that allows us to change the current
direction applied to a load. They are commonly used as motor drivers to change
the direction and the speed of a DC motor and to manage the higher power since
microcontrollers usually don’t have enough current to power an electric motor.

![](media/94c672a74ab05b0bd0b7d325a6d0cce7.png)

The H-Bridge contains four transistors arranged so that the current can be
driven to control the direction of the spin and the angular speed. These
transistors behave as four switches that are controlled in pairs. The current
flows in a different direction depending on which switches are activated. This
allows the direction of the motor itself to be controlled.

![](media/3fd5f0e3bdcb5eef2fc9c4292cca94ed.png)

The image above shows a simplified version of the internal structure of an
H-bridge and how the switches can be controlled to change the motor’s direction.
Switches in the above diagram are transistors that are controlled by the
microcontroller on the Motor Carrier. If we consider a logical HIGH level when
the switch is closed and LOW level when the switch is opened, we have the
following behavior.

| Signal Control A | Signal Control B | Movement          |
|------------------|------------------|-------------------|
| HIGH             | LOW              | Clockwise         |
| LOW              | HIGH             | Counter-Clockwise |
| LOW              | LOW              | Slow Stop         |
| HIGH             | HIGH             | Fast Stop         |

### *Controlling Speed : Pulse Width Modulation*

We change the speed of a motor by controlling the voltage level in its
terminals, The higher the voltage applied, the faster the motor spins. It is
common practice to use a digital signal called PWM (Pulse Width Modulation) to
control the speed of a motor instead of providing analog voltages. This is
possible because since the motor cannot change speed so fast, it acts as a low
pass filter and it behaves as if it is receiving the average (analog) value of
the voltage and current being applied.

![](media/29246d7c720f2f6c7ecce0a97ce6f263.png)

Pulse Width Modulation, or PWM, is a digital modulation technique that consists
of changing the width of a signal’s pulse at a fixed frequency. The width of the
pulse is referred to as the duty-cycle and goes from 0% (minimum width) to 100%
(maximum width).

Most microcontrollers have the ability to generate a dedicated PWM signal. In
general, not all digital pins have this assist option, so if a PWM signal is
required, the datasheet must be checked to determine which pins have this
feature. This project uses **Pigpio** library functions to generate "software"
PWM signals.

Corresponding relation between robot motor and Raspberry Pi Pin:

| Interface    | WiringPi | BCM |
|--------------|----------|-----|
| M1           | P28      | 20  |
| M2           | P29      | 21  |
| PWMA Enable  | P25      | 26  |
| M3           | P22      | 6   |
| M4           | P23      | 13  |
| PWMB Enable  | P26      | 12  |

![](media/9109b0b27758377c300568b5219c4fd8.jpg)

The DC motor we use uses a total of six wires. The four wires called GND, OUT A,
OUT B and VCC are related to the rotary encoder itself. The two wires labelled
M+ and M- connect directly to the motor drive leads, which are hidden under the
rotary encoder chip. Locate the ends of the two motor drive wires.

Torque is delivered to the motor by applying a voltage across these two wires.
The magnitude of the voltage corresponds to the amount of torque applied, and
the sign of the voltage is analogous to the direction of the applied torque.

We control motor rotation by applying PWM signal to M1 and M2 interfaces, and
control motor speed by duty cycle of PWM signal.

DC motors require external control mechanisms to ensure that they are behaving
as expected. In this case, we will use rotary encoders to measure the angle and
speed of the motors while operating. After displacing the motors from their
initial positions, you can read the count value from the encoders to determine
how far each motor has turned in units of encoder counts.

#### Hall Sensor Based Encoders

A Hall effect sensor is capable of detecting the Hall effect. This consists of
the production of a voltage difference across an electrical conductor when a
magnetic field is applied. As the motor turns, the disc rotates past the
sensors. Each time a magnetic pole passes a sensor, the encoder outputs a
digital pulse, also called a “tick”. By counting the frequency of those ticks,
the speed of the motor can be determined.

**Encoder Output Signals**

The encoder has two outputs, one for each Hall effect sensor. The sensors are
positioned so that there is a phase of 90 degrees between them. This means that
the square wave outputs of the two Hall effect sensors on one encoder are 90
degrees out of phase. This is called a quadrature output.

![](media/2af78cfd2479ef19d60658d69cfa67f9.png)

The picture above shows the typical output of an encoder. Having the output
pulsing 90 degrees out of phase allows the direction of the motor’s rotation to
be determined. If output A is ahead of output B, the motor is turning forward.
If output A is behind output B, the motor is turning backward.

As explained earlier, by measuring the frequency of the pulse signal in A or B
(in this case it’s not important from which one), we will obtain the speed at
which the motor is turning. This information can then be used to obtain linear
speed (e.g., the speed of a vehicle).

In our drawing robot, we use two micro DC motors with a gearbox (100:1), and an
encoder . The geared motors will be used to move the wheels of the rover, to
lift the drawing robot.

![](media/e0c8a510dcc8ac6d374059773ef39cc3.png)

The specs of the micro motors with the encoder are:

Speed (No load): 320 RPM

Stall Torque: 2.2 Kg-cm

Pinouts of the DC Motors

There are two pieces of hardware involved in measuring the rotational angle of
the motor. First, the rotary encoder hardware, attached to the motor shaft,
consists of an integrated circuit, which remains stationary, and a magnetic
disk, which rotates along with the motor shaft. As the magnetic poles rotate
relative to the chip, they act on two electromagnetics within the chip such that
they generate two digital signals A and B with the quadrature form discussed
later in this chapter. These signals correspond to the wires labelled OUT A and
OUT B on the rotary encoder chip, as shown in the image below. The wires GND and
VCC are for ground and voltage input, respectively. They will be connected to a
supply voltage source so that current can be provided to generate the A and B
signals.

[**Datasheet geared motor with
encoder**](https://content.arduino.cc/assets/Gear%20motor%20Datasheet.pdf)

![](media/5e5712867d4e53250686e844010c44cf.png)

#### Servo Motor

Servo motors are actuators that allow for precise control of position (angle) or
angular velocity from a microcontroller. They have an embedded control circuit
inside the housing. This circuit can be analog or digital, and this is
determined by the kind of functions the motor is designed to perform. From a
functional perspective, there are two types of servo motors: The standard servo
and continuous rotation servo. In our robot, we use a servo motor to control the
lift and drop of the motor. it also be used in the mechanism to change the pen
color.

Servo motors have three terminals, one for ground (GND), one for power (5V) and
one for the control signal.

![](media/f1e2cd04f0907529f2e0e470c5e0e8f0.png)

To control servo motors, we also use PWM signals. However, even if it is the
same signal modulation we use for the DC motors, in the case of servo motors it
is used in a completely different way. In the case of servos the PWM duty cycle
is translated to a specific turning angle for standard servos, and direction and
speed for continuous servos.

The width of the pulse of the PWM signal for servo control has to be limited
between 1and 2 as represented in the image below, and every command is repeated
every 20 .

![](media/a8f1a6325277288a2a6ea45d54facb7c.png)

[Datasheet of the servo motor](https://content.arduino.cc/assets/GS-9025MG.pdf)

In the motor drive part, two threads are set up to ensure the position
calculation of left and right motors and synchronous motor movement

The following is the code of our motor control module:

## 2.0 WHITEBOARD COORDINATE SYSTEM 

### *Define Distances on the Whiteboard*

**Base**: The physical distance between two pulleys.

**Z1**: Distance of robot to left Pulley.

**Z2**: Distance of robot to right
Pulley.![](media/89ac2a602df835edfda6eefe9b1dd33b.png)

(Length of motor to pulley)

![](media/2ec05f81f8058d3235930922a9bdd0d2.png)

Obviously, as shown in Figure 1, we can calculate the values of x and y by using
the Pythagorean theorem. The position of the robot is located by this method. It
should be emphasized that L1, L2 should be manually measured and assigned when
initializing the robot.

*Apply the Pythagorean theorem for the Distance*

#### *Calculating the Starting Position*

Before we start moving the robot, we need to measure the parameters , , and . We
will use a known value of to compute and . As the robot moves around the
whiteboard, we'll update and based on the encoder measurements. To calculate the
values of and , we can use these known values of , and along with the
**Pythagorean Theorem**. If you drop a perpendicular line from the marker to the
line between the two pulleys, two right-angled triangles are formed, as shown in
the following diagram.

![](media/8bbbbf2c0c4368d228074c7f0059fa4f.png)

The sides of these triangles have the following relationships:

If we solve the second equation for the first equation can be rewritten as,

Expanding this equation and solving for , we end up with the following equations
to solve for and sequentially.

This code implements the above functions:

### *Compute the Current Position*

It is known that the counts returned by the encoder with one turn of the motor
is 300, and the radius of the motor shaft is r, the gear ratio is 100 and 12
counts per revolution of the motor shaft. The rotation Angle of the two motors
can be calculated by the return value of the left and right motors.

We can get the arc length by calculating the arc length formula, where 1/2 of
the arc length is the L we mentioned earlier.

So we can get the value of Z, and then we can use the Pythagorean theorem again
to figure out the value of x and y for the current position

.

The code is implemented as follows:

### *Move to a Sequence of Positions*

The function movetTarget() is mainly to receive the values ​​of the target
coordinates X and Y after image processing, and then combine the current
coordinates to find the difference Z, and use the Z value to derive the count
value that the encoder should reach. This process is actually the reverse of
calculating the current coordinates in the previous article.

### IDENTIFY POSITION LIMITS

So far, we've explored the relationships between the geometry of the robot and
the various forces acting on it. However, the motor equations are expressed in
terms of torque, and not force. Next, we'll bring together all the equations
discussed so far and introduce a relationship between torque and force that will
bind everything together.

Given an x-y position on the whiteboard, it is possible to compute the torque
requirements for the motors. First, use the x and y positions to compute the
angles and formed by the robot's hanging position. Next, compute F1, F2 and T1,
T2. Finally, use T1, T2 to compute and .

To compute and from x and y, use the trigonometric formula for computing the
tangent of an angle:

. To compute F1, F2 from , , use the equations derived before

To compute T1, T2 from F1, F2, recall that the resultant force pulling the robot
in the direction of a pulley equals twice the amount of tension in the string
over that pulley. This is because for a given pulley, the string supports the
robot at two different points.

Finally, compute the required torque from the tension in the string. Each one of
the two strings pulls the motor in a direction perpendicular to the line joining
the center of the spool to the point where the string touches the motor, as
shown in the following diagram.

![](media/0add49c87a08e47e46fd3953aeddb6f8.png)

The magnitude of the torque is then given as the product of the perpendicular
force and the distance between the axis of rotation and the point where the
force is applied. In our case, this distance refers to the radius of the spool
(), and hence the resulting equations are as follows:

After modelling, we get the following picture. his 2D plot will show you which
parts of the whiteboard the robot can and cannot reach. The transparent regions
represent those where the robot can't reach.

![](media/86e4467182fc97166996180d0ea51583.png)

## DRAW PREPROCESSED IMAGES

Contour discovery:

Configure discovery is a method to find the outline of an object based on image
edge extraction. Therefore, the selection of threshold value for edge extraction
will affect the final contour discovery result.

1, input image to gray image CVTColor

2\. Canny was used for edge extraction to obtain binary images

3\. Use FindContours to find the outline

4\. Use DrawContours to draw the outline

Image processing: After reading the picture through opencv, perform grayscale
processing, and then perform binarization processing. Then scan column by
column. Add the detected pixels in each column to the array SUM[]. If the end of
a column SUM[] is empty, it means that the wireless track of this column is
detected. If it is not empty, output the pixel coordinates of the pixel. Then
the coefficient Pix2M is obtained by calculating the ratio between the input
picture and the drawing board, and the picture is stretched or zoomed by this
coefficient to ensure that the picture is output within the drawing range.

The original image and the contour image obtained after image processing:

![](media/90bb399144db4d20591160d3f01413c1.png)

Pixel point map:

![](media/3e927925c988d505b4d79920f4aedd9b.png)

### UI interface

Using HTML combined with CSS elastic layout design UI interface more beautiful
and convenient.

![](media/e9063228cd9f07c877ecee1cad4e6405.jpeg)![](media/87d25b9cef8dbe24b7dc2ddbe67ca819.jpeg)

The main purpose of designing UI interface is to realize remote control of robot
and real-time monitoring PHP (7.3) is selected as the backend language, and
Socket is used as the API of Inter-Process communication in the network
environment. Therefore, communication can be realized only by setting the
socket's receiving and receiving interface in C ++ and PHP, respectively. There
is an example in the file socket directory. In the project, it is incorporated
into the main function.

In addition, you can use Ajax in JavaScript extension jQuery to send JSON stream
data to a PHP file for dynamic interaction, so that you do not have to reload
the page.

![](media/37a0dbf1d04ea36a73d7940f6c03abed.jpeg)

The server configuration selects Nginx to listen on port 80, making it possible
to access the web from devices other than Raspberry Pi. Because of the need for
real-time monitoring, that need to add SSL certificates to the domain name so
that it can be accessed over HTTPS.

![](media/84a803cec9211f33081df4507ab8b32a.jpeg)

### sequence diagram

![](media/773d7f08bb7564dc9f441133a57e0884.png)

### Additional:

Github: https://github.com/yechiyu/Drawing-Robot

Youtube: https://www.youtube.com/watch?v=syOKDyHR77g
