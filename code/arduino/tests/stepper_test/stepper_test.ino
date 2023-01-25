#include <AccelStepper.h>

AccelStepper stepper(AccelStepper::DRIVER, 2, 3);

void setup() {
  // put your setup code here, to run once:
  stepper.setMaxSpeed(20000);
  stepper.setAcceleration(10000);
  stepper.moveTo(800);
}

void loop() {
  // put your main code here, to run repeatedly:
    if (stepper.distanceToGo() == 0) {
      stepper.moveTo(-stepper.currentPosition());
    }
 
    stepper.run();
}
