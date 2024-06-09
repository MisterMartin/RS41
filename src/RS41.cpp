// RS41.cpp
#include "Arduino.h"
#include "RS41.h"

RS41::RS41(HardwareSerial& serial):
_serial(serial) 
{
}

RS41::~RS41() {
  digitalWrite(RS41_GPIO_PWR_PIN, LOW);
}

void RS41::init() {
  Serial7.begin(56700);

  // Increase serial buffer sizes for Teensy 4.1
  Serial7.addMemoryForRead(&_rs41_rx_buffer, sizeof(_rs41_rx_buffer));
  Serial7.addMemoryForWrite(&_rs41_tx_buffer, sizeof(_rs41_tx_buffer));

  // Power cycle the RS41
  pinMode(RS41_GPIO_PWR_PIN, OUTPUT);
  digitalWrite(RS41_GPIO_PWR_PIN, LOW);
  delay(100);
  digitalWrite(RS41_GPIO_PWR_PIN, HIGH);

  // The RS41 immediately sends out a banner
  for (int i = 0; i < 5; i++) {
      String txt = Serial7.readStringUntil('\r');
      if (txt.indexOf("NCAR") != -1) {
        _banner = txt;
        break;
    }
  }

  // Wait for RS41 to get running
  delay(1000);

  // Get the meta data
  String meta;
  for (int i = 0; i < 5; i++) {
      meta = read_meta_data();
      if (meta.indexOf(",") != -1) {
        //Serial.print("Meta: ");
        //Serial.println(meta);
        break;
    }
  }

}

String RS41::banner() {
  return _banner;
}

RS41::RS41SensorData RS41::decoded_sensor_data() {
  RS41SensorData decoded_data;
  decoded_data.valid = false;

  String str_data = read_sensor_data();
  if (str_data.length()) {
    String tokens[17];
    // Add a trailing comma so that all tokens are terminated.
    str_data += ',';
    if (tokenize_string(str_data, tokens, 17)) {
      decoded_data.valid = true;
      decoded_data.frame_count = tokens[0].toInt();
      decoded_data.air_temp_degC = tokens[1].toFloat();
      decoded_data.humdity_percent = tokens[2].toFloat();
      decoded_data.hsensor_temp_degC = tokens[3].toFloat();
      decoded_data.pres_mb = tokens[4].toFloat();
      decoded_data.internal_temp_degC = tokens[5].toFloat();
      decoded_data.module_status = tokens[6].toInt();
      decoded_data.module_error = tokens[7].toInt();
      decoded_data.pcb_supply_V = tokens[8].toFloat();
      decoded_data.lsm303_temp_degC = tokens[9].toFloat();
      decoded_data.pcb_heater_on = tokens[10].toInt();
      decoded_data.mag_hdgXY_deg = tokens[11].toFloat();
      decoded_data.mag_hdgXZ_deg = tokens[12].toFloat();
      decoded_data.mag_hdgYZ_deg = tokens[13].toFloat();
      decoded_data.accelX_mG = tokens[14].toFloat();
      decoded_data.accelY_mG = tokens[15].toFloat();
      decoded_data.accelZ_mG = tokens[16].toFloat();
    }
  }
  return decoded_data;
}

String RS41::read_sensor_data() {
  return(rs41_cmd("RSD"));
}

String RS41::read_meta_data() {
  return(rs41_cmd("RMD"));
}

String RS41::recondition() {
  return(rs41_cmd("RHS"));
}

String RS41::rs41_cmd(const String& cmd) {
  // Note that the default timeout for serial reads is 1000ms.
  // This is generous for sending a command to the RS41, having
  // it process the command, and return the value.
  //
  // If the flush and read wait times are a problem, we
  // can implement a scheme where the command is sent,
  // and we return later to get get the result.
  Serial7.write(cmd.c_str());
  Serial7.write("\r");
  Serial7.flush();
  return Serial7.readStringUntil('\r');
}

bool RS41::tokenize_string(String& source, String (&tokens)[], int nTokens) {
    int token_num = 0;
    bool valid = false;
    int start = 0;
    int end = source.indexOf(',', start);
    while(end != -1)
    {
        tokens[token_num] = source.substring(start, end);
        start = end + 1;
        end = source.indexOf(',', start);
        if (token_num == (nTokens-1)) {
          valid = true;
          break;
        }
        token_num++;
    }

    return valid;
}
