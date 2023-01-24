#include <PID_v1.h>
#include <HCSR04.h>
#include <Servo.h>
#include <SimpleKalmanFilter.h>

const int SERVO_PIN = 3;
const int ECHO_PIN = 6;
const int TRIG_PIN = 5;
const int SERVO_MAX = 1700;
const int SERVO_MIN = 1300;
const int SERVO_CENTRE = 1500;

const double MEASURMENT_ERROR = 0.03;
const double VARIANCE = 0.01;
const double KP = 1.0;
const double KI = 0.0;
const double KD = 0.0;
const double SET_POINT = 15.0;

double ball_position;
int angle, target_angle;
double setPoint, input, output;

Servo servo;
HCSR04 sensor(TRIG_PIN, ECHO_PIN);
SimpleKalmanFilter filter(MEASURMENT_ERROR, MEASURMENT_ERROR, VARIANCE);
PID pid(&input, &output, &setPoint, KP, KI, KD, DIRECT);

void setup()
{
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
  servo.writeMicroseconds(SERVO_CENTRE);
  setPoint = SET_POINT;
  pid = PID(&input, &output, &setPoint, KP, KI, KD, DIRECT);
  pid.SetMode(AUTOMATIC);
  pid.SetOutputLimits(SERVO_MIN, SERVO_MAX);
}

void readSensor()
{
  double reading = sensor.dist();
  if (reading > 2 && reading < 18)
  {
    ball_position = filter.updateEstimate(reading);
  }
}

void moveToPosition(int target_angle)
{
  while (angle != target_angle)
  {
    if (angle > target_angle)
    {
      angle -= 1;
    }
    else
    {
      angle += 1;
    }
    servo.writeMicroseconds(angle);
    delay(1);
  }
}

void loop()
{
  readSensor();
  input = setPoint - ball_position;
  pid.Compute();
  moveToPosition(angle + output);
  Serial.println(output);
}
