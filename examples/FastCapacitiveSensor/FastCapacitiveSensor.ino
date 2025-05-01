#include <FastCapacitiveSensor.h>
// the send pin should be a pin that can be used with the digitalWrite() function
// the receive pin MUST be an analog pin. The library uses analogRead() internally.
FastCapacitiveSensor sensor1(A0, A1, 10, 10, 0.2);
FastCapacitiveSensor sensor2(A2, A3, 10, 10, 0.2);

void setup() {
  Serial.begin(9600);
  sensor1.begin();
  sensor2.begin();
}

void loop() {
  Serial.print(sensor1.touch());
  Serial.print("\t");
  Serial.println(sensor2.touch());
}
