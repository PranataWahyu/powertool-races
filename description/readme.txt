Here's what we came up with so far:

- A timing system for measuring race times.
- A system for measuring and plotting the acceleration of the racers over
  time.


The timing circuit is Arduino-based, using an IR beam interrupt detector
(https://www.adafruit.com/products/2168). The detector is hooked up to the
Arduino on an interrupt routine (see code at
https://github.com/anthonyaue/powertool-races/blob/master/arduino/interrupt_ir/interrupt_ir.ino).

The acceleration is measured by velcro'ing micro:bits to the actual racers.
They transmit the accelerometer data to a master micro:bit using LE Bluetooth.

The master micro:bit reads the race start signal from a switch and the end
race signal from an output pin of the Arduino (we were
unable to read the very short pulse from the IR sensor using the micro:bits).

The slave micro:bits (the ones attached to the racers) just broadcast their
accelerometer data continuously.

Currently the sketch for timing is separate from the sketch for reading and
accumulating the accelerometer data, but it should be trivial to combine the
two.

When the master micro:bit gets the start signal, it accumulates the
accerlerometer data, waiting for the stop signal.

When it gets the stop signal, it will write the total time and the
accelerometer data out to the serial port.

A program on the host computer (connected via USB serial to the master
micro:bit) listens for the race results and displays them in some wonderful
shiny fashion.


