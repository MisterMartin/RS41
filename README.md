# RS41 Arduino Library
NCAR RS41 sensor support library for Teensy 4.1
(should work for general Arduinos).

Dependencies: None

## Installation
```sh
cd Documents/arduino/libraries # Or wherever your Arduino libraries are
git clone https://github.com/MisterMartin/RS41.git
```
Open an example sketch in the Arduino IDE and run it.

## Examples
- `examples/RS41test.ino` samples the RS41 and prints data to the serial console.
  At program start, you are prompted whether you want to do a sensor regeneration or not.

- `examples/RS41csv` samples from the RS41 and writes to a CSV file on the SD card, and to the serial console.
  A new CSV file is created everytime the program is run. The filename is `RS41_data_nnnnn.csv`, with
  nnnnn being incremented each time.
  Unfortunately there is no system clock available, and so there are no timestamps for the
  data files or data lines. You'll just have to keep track of the time for each file name
  (it is printed to the console).


  


