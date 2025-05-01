#include "FastCapacitiveSensor.h"
#include <math.h>

FastCapacitiveSensor::FastCapacitiveSensor(int sendPin, int receivePin, int frequency, int breakThreshold, double exceptRatio, int adcBits) : sendPin(sendPin), receivePin(receivePin), numReads(frequency), breakThreshold(breakThreshold), exceptRatio(exceptRatio)  {
  adcmax = 1 << adcBits;
  inputThreshold = adcmax * 0.9;
  except = frequency * exceptRatio;
  use = frequency - 2 * except;
}

static void swap(double* a, double* b) {
  double c = *a;
  *a = *b;
  *b = c;
}

static void sort(double* array) {
  int size = sizeof(array) / sizeof(double);
  for(int i = 0;i < size;i++)
    for(int j = size - 1;j > i; j--)
      if(array[j] < array[j - 1])
        swap(&array[j], &array[j - 1]);
}

void FastCapacitiveSensor::begin() {
  pinMode(sendPin, OUTPUT_OPENDRAIN);
  pinMode(receivePin, INPUT);
}

double FastCapacitiveSensor::touch() {
  double values[numReads];

  for (int i = 0; i < numReads; i++) {
    double val = 0;
    digitalWrite(sendPin, HIGH);
    unsigned long starttim = micros();
    while (analogRead(receivePin) < inputThreshold) {
      unsigned long t1 = micros() - starttim;
      if (t1 > breakThreshold) {
        int v1 = analogRead(receivePin);
        val = t1 * log(1.0 - 0.9) / log(1.0 - ((double)v1 / (double)adcmax));
        break;
      }
    }
    digitalWrite(sendPin, LOW);
    delayMicroseconds(10);

    if (val > 0) {
      values[i] = val;
    } else
      i--;
  }
  if (except > 0) {
    sort(values);
  }
  double sum = 0;
  for (int i = except;i < numReads - except;i++)
    sum += values[i];
  return sum / use;
}