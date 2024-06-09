// Create CSV suitable outout from the RS41

#include <RS41.h>
#include "SD.h"
#include "SPI.h"

// A new file is created every time that the program is run.
//
// The data file names will take the form of:
// DATA_FILE_BASE_NAMEnnnnnDATA_FILE_EXT
// e.g. RS41_data_00092.csv

#define DATA_FILE_BASE_NAME "RS41_data_"
#define DATA_FILE_EXT ".csv"

bool first_loop = true;
RS41 rs41(Serial7);

// The csv file to create. It will be empty
// if we are unable to access the SD card.
String csv_file_name = "";
File csv_file;

void setup()
{
  Serial.begin(115200);
  while (!Serial) { ; }

  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("Unable to acces the SD card, data WILL NOT be saved to a file");
  } else {
    csv_file_name = next_file_name();
  }

  // Configure the RS41 serial port, power on the RS41, capture the banner, query the metadata.
  rs41.init();
}

void loop()
{
  if (first_loop) {
    Serial.println(rs41.sensor_data_var_names);
    first_loop = false;
  }

  // A delay at the start prevents missing the first data frame
  delay(2000);

  RS41::RS41SensorData sensor_data = rs41.decoded_sensor_data();
  if (sensor_data.valid) {
    // Create the CSV file 
    Serial.print(sensor_data.frame_count); Serial.print(",");
    Serial.print(sensor_data.air_temp_degC); Serial.print(",");
    Serial.print(sensor_data.humdity_percent); Serial.print(",");
    Serial.print(sensor_data.hsensor_temp_degC); Serial.print(",");
    Serial.print(sensor_data.pres_mb); Serial.print(",");
    Serial.print(sensor_data.internal_temp_degC); Serial.print(",");
    Serial.print(sensor_data.module_status); Serial.print(",");
    Serial.print(sensor_data.module_error); Serial.print(",");
    Serial.print(sensor_data.pcb_supply_V); Serial.print(",");
    Serial.print(sensor_data.lsm303_temp_degC); Serial.print(",");
    Serial.print(sensor_data.pcb_heater_on); Serial.print(",");
    Serial.print(sensor_data.mag_hdgXY_deg); Serial.print(",");
    Serial.print(sensor_data.mag_hdgXZ_deg); Serial.print(",");
    Serial.print(sensor_data.mag_hdgYZ_deg); Serial.print(",");
    Serial.print(sensor_data.accelX_mG); Serial.print(",");
    Serial.print(sensor_data.accelY_mG); Serial.print(",");
    Serial.print(sensor_data.accelZ_mG);
    Serial.println();
  } else {
    Serial.println("Unable to obtain RS41 sensor data");
  }
}

String next_file_name() {
  // Scan the root directory of the SD card, and 
  // find the highest numbered data file. Return a
  // string with the next higher numbered file name.

  int next_file_num = 0;
  File dir = SD.open("/");
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }

    String file_name = entry.name();
    if (file_name.startsWith(DATA_FILE_BASE_NAME) && file_name.endsWith(DATA_FILE_EXT)) {
      String file_num = file_name.substring(strlen(DATA_FILE_BASE_NAME), file_name.indexOf(DATA_FILE_EXT));
      if (isIntStr(file_num)) {
        int n = file_num.toInt();
        if (next_file_num <= n) {
          next_file_num = n+1;
        }
      } 
    }
    if (entry.isDirectory()) {
    } else {
    }
    entry.close();
  }
  String next_name = String(DATA_FILE_BASE_NAME) + String(next_file_num) + String(DATA_FILE_EXT);
  return next_name;
}

boolean isIntStr(String str) {
  for(unsigned int i=0;i<str.length();i++) {
    if(!isDigit(str.charAt(i))) {
      return false;
    }
  }
  return true;
}

