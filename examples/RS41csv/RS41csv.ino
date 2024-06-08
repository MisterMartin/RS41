// Create CSV suitable outout from the RS41

#include <RS41.h>

bool first_loop = true;
RS41 rs41(Serial7);

void setup()
{
  Serial.begin(115200);
  // Configure the serial port, power on the RS41, capture the banner, query the metadata.
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
