// RS41.cpp
#include "Arduino.h"
#include "RS41.h"

// Constructor
RS41::RS41() {
  _exampleVar = 0;
}

// Initialization method
void RS41::begin() {
  Serial.begin(9600);
}

// Method to print "Hello, World!"
void RS41::printHello() {
  Serial.println("Hello, World!");
}
