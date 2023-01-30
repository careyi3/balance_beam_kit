#include <PID_v1.h>
#include <HCSR04.h>
#include <AccelStepper.h>
#include <SimpleKalmanFilter.h>

const int STEP_PIN = 2;
const int DIR_PIN = 3;
const int ECHO_PIN = 6;
const int TRIG_PIN = 5;
const int STEPPER_MAX = 800;
const int STEPPER_MIN = -800;

const double MEASURMENT_ERROR = 0.03;
const double VARIANCE = 1;
const double KP = 50.0;
const double KI = 10.0;
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
  stepper.setMaxSpeed(6000);
  stepper.setAcceleration(12000);
  stepper.setMinPulseWidth(5);
  setPoint = SET_POINT;
  pid = PID(&input, &output, &setPoint, KP, KI, KD, DIRECT);
  pid.SetMode(AUTOMATIC);
  pid.SetOutputLimits(STEPPER_MIN, STEPPER_MAX);
}

void readSensor()
{
  double reading = sensor.dist();
  if (reading > 2.0 && reading < 25.00)
  {
    ball_position = filter.updateEstimate(reading) / 100.00;
  }
}

void move()
{
  stepper.runToNewPosition(-output);
}

void loop()
{
  readSensor();
  double h = ball_position - 0.135;
  double a = stepper.currentPosition() * 0.000098;
  input = h * cos(a);
  pid.Compute();
  move();
}
