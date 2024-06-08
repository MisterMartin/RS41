// BasicExample.ino

#include <RS41.h>

RS41 rs41(Serial7); // Create an instance of RS41

bool recondition = false;

void setup()
{
  Serial.begin(115200);
  Serial.print("RS41test build ");
  Serial.print(__DATE__);
  Serial.print(" ");
  Serial.println(__TIME__);

  Serial.println("Do you want to recondition [y/n]? ");
  while (Serial.available() == 0) {}
  String ans = Serial.readString().trim();
  if ((ans=="Y") || (ans=="y")) {
    recondition = true;
  }

  rs41.init();

}

void loop()
{

  if (recondition) {
    String recond = rs41.recondition();
    if (!recond.length()){
      Serial.println("RS41 did not respond to RHS");
    } else {
      Serial.print("Recondition: ");
      Serial.println(recond);
      recondition = false;
    }
  }
  String sensor = rs41.read_sensor_data();
  if (!sensor.length()){
    Serial.println("RS41 did not respond to RSD");
  } else {
    Serial.print("Sensor: ");
    Serial.println(sensor);
  }
  delay(2000);
}
