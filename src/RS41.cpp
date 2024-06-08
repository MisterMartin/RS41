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
  _serial.begin(56700);

  // Increase serial buffer sizes for Teensy 4.1
  //_serial.addMemoryForRead(&_rs41_rx_buffer, sizeof(_rs41_rx_buffer));
  //_serial.addMemoryForWrite(&_rs41_tx_buffer, sizeof(_rs41_tx_buffer));

  // Power cycle the RS41
  pinMode(RS41_GPIO_PWR_PIN, OUTPUT);
  digitalWrite(RS41_GPIO_PWR_PIN, LOW);
  delay(100);
  digitalWrite(RS41_GPIO_PWR_PIN, HIGH);

  // The RS41 immediately sends out a banner
  String banner;
  for (int i = 0; i < 5; i++) {
      banner = _serial.readStringUntil('\r');
      if (banner.indexOf("NCAR") != -1) {
        Serial.print("Banner: ");
        Serial.println(banner);
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
        Serial.print("Meta: ");
        Serial.println(meta);
        break;
    }
  }

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
  _serial.write(cmd.c_str());
  _serial.write("\r");
  _serial.flush();
  return _serial.readStringUntil('\r');
}
