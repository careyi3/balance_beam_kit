#include <PID_v1.h>
#include <HCSR04.h>
#include <AccelStepper.h>
#include <SimpleKalmanFilter.h>

const int STEP_PIN = 3;
const int DIR_PIN = 2;
const int ECHO_PIN = 6;
const int TRIG_PIN = 5;
const int M0_PIN = 8;
const int M1_PIN = 9;
const int M2_PIN = 10;
const int ENABLE_PIN = 12;
const int STEP_MODE = 5;
const int STEP_MODES[6][4] = {
    {1, 0, 0, 0},  // STEP_MODE = 0
    {2, 1, 0, 0},  // STEP_MODE = 1
    {4, 0, 1, 0},  // STEP_MODE = 2
    {8, 1, 1, 0},  // STEP_MODE = 3
    {16, 0, 0, 1}, // STEP_MODE = 4
    {32, 1, 1, 1}  // STEP_MODE = 5
};

const double MEASUREMENT_ERROR = 0.04;
const double VARIANCE = 1;
const double KP = 27.50;
const double KI = 15.0;
const double KD = 6.0;
const double SET_POINT = 0.0;

double ball_position;
double setPoint, input, output;
double radiansPerStep;

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);
HCSR04 sensor(TRIG_PIN, ECHO_PIN);
SimpleKalmanFilter filter(MEASUREMENT_ERROR, MEASUREMENT_ERROR, VARIANCE);
PID pid(&input, &output, &setPoint, KP, KI, KD, DIRECT);

void setup()
{
  pinMode(M0_PIN, OUTPUT);
  pinMode(M1_PIN, OUTPUT);
  pinMode(M2_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);
  digitalWrite(ENABLE_PIN, HIGH); // Disable Motor

  double degreesPerStep = 360.00 / (200.00 * STEP_MODES[STEP_MODE][0]); // Assuming a 200 step motor
  radiansPerStep = degreesPerStep * (PI / 180.00);
  stepper.setMaxSpeed(25000);
  stepper.setAcceleration(15000);
  stepper.setMinPulseWidth(5);
  digitalWrite(M0_PIN, STEP_MODES[STEP_MODE][1]);
  digitalWrite(M1_PIN, STEP_MODES[STEP_MODE][2]);
  digitalWrite(M2_PIN, STEP_MODES[STEP_MODE][3]);

  int stepperMax = 25 * STEP_MODES[STEP_MODE][0]; // Allow the motor to move about an 1/8 of a rotation +/-
  int stepperMin = -1 * stepperMax;
  setPoint = SET_POINT;
  pid = PID(&input, &output, &setPoint, KP, KI, KD, DIRECT);
  pid.SetMode(AUTOMATIC);
  pid.SetOutputLimits(stepperMin, stepperMax);

  for (int i = 0; i < 10; i++) // Delay for 2 seconds reading sensor to allow initial values to settle
  {
    readSensor();
    delay(200);
  }
  digitalWrite(ENABLE_PIN, LOW); // Enable Motor
}

void readSensor()
{
  double reading = sensor.dist();
  if (reading > 2.0 && reading < 25.00)
  {
    ball_position = filter.updateEstimate(reading);
  }
}

void move()
{
  stepper.runToNewPosition(-output);
}

void loop()
{
  readSensor();
  double h = 13.5 - ball_position;
  double a = stepper.currentPosition() * radiansPerStep;
  input = h * cos(a);
  pid.Compute();
  move();
}
