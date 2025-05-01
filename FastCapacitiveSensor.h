#ifndef FastCapacitiveSensor_h
#define FastCapacitiveSensor_h

#include "Arduino.h"

class FastCapacitiveSensor {
public:
  FastCapacitiveSensor(int sendPin, int receivePin, int numReads, int breakThreshold, double exceptRatio, int adcBits=10);
  void begin();
  double touch();

private:
  int numReads;
  int breakThreshold;
  double exceptRatio;
  int sendPin, receivePin;
  int adcmax;
  double inputThreshold;
  int except, use;
};

#endif