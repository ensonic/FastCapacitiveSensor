#ifndef FastCapacitiveSensor_h
#define FastCapacitiveSensor_h

#include "Arduino.h"

class FastCapacitiveSensor {
public:
  FastCapacitiveSensor(int sendPin, int receivePin, int numReads, int breakThreshold, float exceptRatio, int adcBits=10);
  void begin();
  unsigned long touch();

private:
  int numReads;
  int breakThreshold;
  float exceptRatio;
  int sendPin, receivePin;
  int adcmax;
  float inputThreshold;
  int except, use;
};

#endif