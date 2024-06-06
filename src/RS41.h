// RS41.h
#ifndef RS41_H
#define RS41_H

#include "Arduino.h"

class RS41 {
  public:
    RS41();              // Constructor
    void begin();             // Initialization method
    void printHello();        // Example method to print "Hello, World!"
  private:
    int _exampleVar;          // Example private variable
};

#endif
