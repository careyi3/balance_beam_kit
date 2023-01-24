#include <Servo.h>

Servo servo;
int position, target;

void setup() {
  // put your setup code here, to run once:
  servo.attach(3);
  servo.writeMicroseconds(1500);
  position = 1500;
  target = 1700;
}

void loop() {
 if (position == 1700)
 {
   target = 1300;
 }
 if (position == 1300)
 {
   target = 1700;
 }
 while(position != target)
 {
   if (position > target)
   {
     position -= 1;
   } else
   {
     position += 1;
   }
   servo.writeMicroseconds(position);
   delay(1);
 }
}
