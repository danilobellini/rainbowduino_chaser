..
  Copyright (c) 2014 Danilo de Jesus da Silva Bellini
  License is MIT, see COPYING.txt for more details.

Chaser (Rainbowduino game)
==========================

Chaser game for Rainbowduino with MMA7660 Orientation/Motion Detection Sensor

Simple accelerometer-controled game for the Rainbowduino board, tested with its
version 3 (which includes USB), but it should work with older versions as well.


Hardware Needed
===============

All equipment needed is:

* Rainbowduino "LED driver platform" (Arduino compatible controller)
* Rainbowduino-compatible 8x8 RGB LED matrix
* An accelerometer based on the Freescale MMA7660FC 3-axis orientation/motion
  detection sensor (5V supply and I/O).

Besides the obvious, such as the wire for connecting the accelerometer to the
Rainbowduino and something to supply power to the board (either a USB source or
another DC source such as a 9V battery).


Hardware connections
====================

The connection is quite simple, the starting steps on how to fit the 8x8 LED
matrix in the board can be seen in the beginning of a `Grand Meek blog post`_
with useful pictures.

For a "tl;dr" approach, just buy an accelerometer circuit which already have
the MMA7660 pins "wrapped" to work with a 5V supply and Rainbowduino I/O
values, such as `SS-SEN21853P`_. The "wrapped" SDA, SCL, as well as the supply
pins (VCC and GND) could be directly connected to the respective ones in the
Rainbowduino circuit.

Make sure the Rainbowduino power supply switch is at "USB" when connecting it
to the computer to "upload" the project, and that you won't ever supply it from
both the USB and the DC connector simultaneously.


Hardware details
================

You don't need to know about the details unless you want to build your own
hardware circuit instead of buying an assembled accelerometer and Rainbowduino
directly.

For using the MMA7660 SMD IC directly, the first thing one should know is that
the power supply from a Rainbowduino VCC pin shouldn't be used directly by the
MMA7660, since this sensor is a low power operation device, and the AVDD/DVDD
pins couldn't have more than 3.6V.  A 3.3V supply would be enough, thats what
`SS-SEN21853P`_ does with a 3.3V regulator (XC6206P332MR).

The Rainbowduino SDA ad SCL pins (I²C data and clock pins, respectively) should
be connected to the accelerometer SDA and SCL pins, respectively, by means of a
small circuit for each. That circuit is needed due to the `ATmega328`_ two-wire
serial interface characteristics, which needs to have at least 70% VCC supply
voltage to safely classify an input as a high state value, which means 3.5V for
a 5V supply (more than our 3.3V regulated supply). For that, `SS-SEN21853P`_
uses a `BSN20 N-channel FET`_.

As the Rainbowduino and the accelerometer boards discussed here are both open
hardware, you're highly encouraged to see their schematics even if you're not
going to build them manually. Also, an I²C connection schematics and more
details are explicit in the `MMA7660FC datasheet`_.

.. _`Grand Meek blog post`: http://grantmeek.co.uk/?p=197
.. _`SS-SEN21853P`:
  http://www.seeedstudio.com/wiki/Grove_-_3-Axis_Digital_Accelerometer%28%C2%B11.5g%29
.. _`ATmega328`: http://www.atmel.com/devices/ATMEGA328.aspx
.. _`BSN20 N-channel FET`: http://www.nxp.com/documents/data_sheet/BSN20.pdf
.. _`MMA7660FC datasheet`:
  http://www.freescale.com.cn/files/sensors/doc/data_sheet/MMA7660FC.pdf


Software Installation
=====================

To install/upload the chaser game to the board, first install the only project
dependency, the Rainbowdino Library:

http://www.seeedstudio.com/wiki/Rainbowduino_v3.0#Resources

Newer `Arduino IDE`_ versions (since 1.0.5) have a zipped library installation
feature in the *Sketch -> Import Library...* menu. For older versions, the
library contents should be put unzipped as a subdirectory in the
``~/sketchbook/libraries`` directory, or something alike for your operating
system. In such cases, the `Grand Meek blog post`_ discussed previously and a
`Mark Polmer blog post`_ might help finding it (besides other useful
information they have for beginners).

After that, it's enough to open the `chaser.ino` file in the Arduino IDE and
upload it, but before uploading, one have to config the IDE, which means, for
Linux:

1. Connect Rainbowduino to the USB
2. Select "Arduino Duemilanove w/ ATmega328" in *Tools -> Board*
3. Select ``/dev/ttyUSB0`` in *Tools -> Serial Port*

And something equivalent for other operating systems. See that two blog posts
for more information on these.


.. _`Arduino IDE`: http://arduino.cc/en/Guide/Environment
.. _`Mark Polmer blog post`:
  http://www.anyware.co.uk/2005/2012/01/17/getting-started-with-arduino-rainbowduino/


How to play
===========

To start the game, just supply power to the Rainbowduino after the game is
installed. Remember to change the USB-DC supply power connector switch when
needed (I'm using a guitar pick for that, so I don't need to remove the LED
matrix).

To play, just turn the accelerometer, which should control the green pixel in
the LED matrix.


Game goal
=========

Hardcoded? There's none. As you control the green "pixel" and there's a blue
"pixel" walking around, you can chase it, but you can as well try to get as far
as possible from it. The light is red when both pixels are in the same
position, so you can know when you won/lost if that's the rules you're
following.

There's many changes that can be done to this simple game, for example:

* Add some artificial intelligence to it (both for chasing and running away)
* Create as scenario, with objects which the pixels can hit
* Toggle the goal and/or scenario when pixels hit together


----

License is MIT, see `COPYING.txt`_ for more details.
By Danilo J. S. Bellini

.. _`COPYING.txt`: COPYING.txt
