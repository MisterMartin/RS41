// BasicExample.ino

#include <RS41.h>

RS41 myLib; // Create an instance of RS41

void setup() {
  myLib.begin();    // Initialize the library
  myLib.printHello(); // Use the printHello method
}

void loop() {
  // Your loop code here
}
