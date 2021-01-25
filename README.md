# Drawing-Roboot

This project has realized a drawing machine hand that can draw a graph according to the picture. Our idea is to generate images after drawing on a computer drawing board or on a mobile device and perform some processing on Raspberry Pi, using image processing, trajectory calculation, and trajectory optimization for path planning, then pass pictures to Raspberry Pi through a WIFI module. The Drawing Robot Draws an image on a whiteboard of an image of a picture from a computer. The Robot utilizes code and motor control system theory to convert a physical image to a position digital format and onto a whiteboard. In this vision, we will use servo motors, DC motors with encoders, and some hardware.

# Key Words:
IMAGE PROCESSING 
MATH COMPUTATIONS
COORDINATE GEOMETRY
ROBOT MOVEMENT
TRIGONOMETRY

<img scr="https://github.com/yechiyu/Drawing-Robot/blob/main/picture/pic5.jpg">

### Everything We Need (~100£ or less)
* [Raspberry Pi 4 Model B] 	£ 54 (https://thepihut.com/products/raspberry-pi-4-model-b?variant=20064052740158)
* [Official UK Raspberry Pi 4 Power Supply (5.1V 3A)]   £ 7.50  (https://thepihut.com/products/raspberry-pi-psu-uk?variant=20064004505662)
* ['NOOBS' Preinstalled Micro SD Card (Latest v3.4.0)]  £ 9     (https://thepihut.com/products/noobs-preinstalled-sd-card?variant=20649315598398)
* [USB 2.0 MicroSD Card Reader (MicroSD to USB)]  £ 2  (https://thepihut.com/products/usb-2-0-microsd-card-reader-microsd-to-usb?variant=26720977160)
* [Premium Female/Female Jumper Wires - 20 x 6" (150mm)]  £ 2  (https://thepihut.com/products/premium-female-female-jumper-wires-20-x-6-150mm?variant=27739698449)
* [Raspberry Pi Motor Driver Board]  £ 28  (https://thepihut.com/products/raspberry-pi-motor-driver-board?variant=32051314589758)
* [3D printing model] £ 10 <br/>

![alt 3D printing model](https://github.com/yechiyu/Drawing-Robot/blob/main/picture/2.jpg)
* [2*GS-9025MG 2.5kg Mini Throttle Steering RC Servo Metal Gears 1/16] £10.99 
* [Dc Gear motors can match encoder] (http://ttmotor.com/productshow.php?sid=208&id=102) <br/>

![alt DC motor and servo motor](https://github.com/yechiyu/Drawing-Robot/blob/main/picture/1.jpg)

# Equipment assembly

# The operating environment
* Ubuntu 20.10 ran in raspberry.
* Initialize the environment so that remote connections are possible.
* `sudo apt update`
* `sudo apt install openssh-server`
* `sudo passwd username`
* `ifconfig` getting IP
* `ssh <username>@<ip_address>` The remote connection
  
## install and start NGINX
* `sudo apt install nginx`
* `sudo /etc/init.d/nginx start`
* Site root `/var/www/html`

## install PHP
* `sudo apt install php-fpm`

## Start PHP in NGINX
### configuration
* `cd /etc/nginx`
* `sudo nano sites-enabled/default`
* find the line `index index.html index.htm;`, then add `index.php` after index.

* find the section <br/>
```
location ~ \.php$ {
    include snippets/fastcgi-php.conf;
    fastcgi_pass unix:/var/run/php5-fpm.sock;
}
```
* and removing the `#` before the each line.
### reload the configuration file
* `sudo /etc/init.d/nginx reload`
### Download the repositories
* `git clone https://github.com/yechiyu/Drawing-Robot.git`
* `cd Drawing-Robot`
