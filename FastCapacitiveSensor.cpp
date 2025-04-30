#include "FastCapacitiveSensor.h"
#include <math.h>

FastCapacitiveSensor::FastCapacitiveSensor() {
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

void FastCapacitiveSensor::begin(int send, int receive, int frequency, int breakthreshold, double exceptratio, int adcBits) {
  SEND = send;
  RECEIVE = receive;
  FREQUENCY = frequency;
  BREAKTHRESHOLD = breakthreshold;
  EXCEPTRATIO = exceptratio;
  ADCMAX = 1 << adcBits;
  INPUTTHRESHOLD = ADCMAX * 0.9;
  EXCEPT = FREQUENCY * EXCEPTRATIO;
  USE = FREQUENCY - 2 * EXCEPT;
}

double FastCapacitiveSensor::touch() {
  double VAL[FREQUENCY];

  for (int i = 0; i < FREQUENCY; i++) {
    double val = 0;
    digitalWrite(SEND, HIGH);
    unsigned long starttim = micros();
    while (analogRead(RECEIVE) < INPUTTHRESHOLD) {
      unsigned long t1 = micros() - starttim;
      if (t1 > BREAKTHRESHOLD) {
        int v1 = analogRead(RECEIVE);
        val = t1 * log(1.0 - 0.9) / log(1.0 - ((double)v1 / (double)ADCMAX));
        break;
      }
    }
    digitalWrite(SEND, LOW);
    delayMicroseconds(10);

    if (val > 0) {
      VAL[i] = val;
    } else
      i--;
  }
  sort(VAL);
  double VALsum = 0;
  for (int i = EXCEPT;i < FREQUENCY - EXCEPT;i++)
    VALsum += VAL[i];
  return VALsum / USE;
}