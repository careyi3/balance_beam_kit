#include <HCSR04.h>
#include <SimpleKalmanFilter.h>

HCSR04 sensor(5, 6);
SimpleKalmanFilter filter(0.03, 0.03, 0.01);

void setup() {
  Serial.begin(9600);
}

void loop() {
  double reading = sensor.dist();
  if (reading > 2 && reading < 18)
  {
    Serial.print(reading);
    Serial.print(",");
    Serial.println(filter.updateEstimate(reading));
  }
  delay(20);
}
