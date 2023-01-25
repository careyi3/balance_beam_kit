#include <PID_v1.h>
#include <HCSR04.h>
#include <AccelStepper.h>
#include <SimpleKalmanFilter.h>

const int STEP_PIN = 2;
const int DIR_PIN = 2;
const int ECHO_PIN = 6;
const int TRIG_PIN = 5;
const int STEPPER_MAX = 800;
const int STEPPER_MIN = -800;

const double MEASURMENT_ERROR = 0.03;
const double VARIANCE = 0.01;
const double KP = 100.0;
const double KI = 0.0;
const double KD = 0.0;
const double SET_POINT = 0.0;

double ball_position;
double setPoint, input, output;

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);
HCSR04 sensor(TRIG_PIN, ECHO_PIN);
SimpleKalmanFilter filter(MEASURMENT_ERROR, MEASURMENT_ERROR, VARIANCE);
PID pid(&input, &output, &setPoint, KP, KI, KD, DIRECT);

void setup()
{
  Serial.begin(9600);
  stepper.setMaxSpeed(20000);
  stepper.setAcceleration(10000);
  setPoint = SET_POINT;
  pid = PID(&input, &output, &setPoint, KP, KI, KD, DIRECT);
  pid.SetMode(AUTOMATIC);
  pid.SetOutputLimits(STEPPER_MIN, STEPPER_MAX);
}

void readSensor()
{
  double reading = sensor.dist();
  if (reading > 2.0 && reading < 20.00)
  {
    ball_position = filter.updateEstimate(reading);
  }
}

void move()
{
  if (output > STEPPER_MIN && output < STEPPER_MAX)
  {
    stepper.moveTo(output);
  }
  stepper.run();
}

void loop()
{
  readSensor();
  input = ball_position - 9.0;
  pid.Compute();
  move();
}
