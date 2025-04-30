#ifndef FastCapacitiveSensor_h
#define FastCapacitiveSensor_h

#include "Arduino.h"

class FastCapacitiveSensor {
public:
  FastCapacitiveSensor();
  void begin(int send, int receive, int frequency, int breakthreshold, double exceptratio, int adcBits=10);
  double touch();

private:
  int FREQUENCY;
  int BREAKTHRESHOLD;
  double EXCEPTRATIO;
  int SEND;
  int RECEIVE;
  int ADCMAX;
  double INPUTTHRESHOLD;
  int EXCEPT, USE;
};

#endif