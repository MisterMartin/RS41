# RS41 Arduino Library
NCAR RS41 sensor support library for Teensy 4.1.

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

Output from `RS41csv`:
```
Creating RS41_data_00018.csv
frame_count,air_temp_degC,humdity_percent,hsensor_temp_degC,pres_mb,internal_temp_degC,module_status,module_error,pcb_supply_V,lsm303_temp_degC,pcb_heater_on,mag_hdgXY_deg,mag_hdgXZ_deg,mag_hdgYZ_deg,accelX_mG,accelY_mG,accelZ_mG
1,23.14,42.37,23.50,770.57,26.78,6152,0,5.10,23.40,0,327.60,326.30,23.50,522.00,341.00,784.00
2,23.17,42.31,23.53,770.74,26.82,6152,0,5.90,23.40,0,327.60,326.70,22.60,527.00,336.00,803.00
3,23.27,42.40,23.54,770.76,26.85,6152,0,5.90,23.40,0,326.50,327.10,23.50,517.00,344.00,795.00
4,23.34,42.37,23.57,770.67,26.88,6152,0,5.90,23.40,0,327.40,326.20,23.10,529.00,339.00,788.00
5,23.57,42.29,23.57,770.44,26.88,6152,0,5.90,23.40,0,326.90,326.70,23.30,528.00,344.00,801.00
6,23.46,42.12,23.58,770.68,26.88,6152,0,5.90,23.40,0,327.10,326.90,23.10,519.00,341.00,794.00
7,23.40,42.13,23.57,770.68,26.92,6152,0,5.90,23.40,0,326.90,326.30,23.60,526.00,344.00,787.00
```



  


