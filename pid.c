#include <PID.h>  // updated to maintained PID library
#include <math.h>

double Setpoint, Input, Output;
double lastValidInput = 0;  // track last sane input value
double Kp, Ki, Kd;

PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

#define INPUT_MIN 0
#define INPUT_MAX 1023
#define EMERGENCY_TIMEOUT 30000  // 30 seconds

void setup() {
  Setpoint = 100;
  Input = analogRead(A0);
  if (Input < INPUT_MIN || Input > INPUT_MAX) {
    Input = lastValidInput;
  } else {
    lastValidInput = Input;
  }
  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(100);
  myPID.SetOutputLimits(0, 255);
  pinMode(3, OUTPUT);
  autoTune();
}

void loop() {
  Input = analogRead(A0);
  if (Input < INPUT_MIN || Input > INPUT_MAX) {
    Input = lastValidInput;
  } else {
    lastValidInput = Input;
  }
  myPID.Compute();
  int safeOutput = constrain((int)Output, 0, 255);
  analogWrite(3, safeOutput);
}

void autoTune() {
  double highSetpoint = 110;
  double lowSetpoint = 90;
  double Ku, Pu;
  double lastInput = Input;
  int sampleTime = 1000;
  int steps = 30;
  unsigned long startTime = millis();

  //run relay experiment
  for (int i = 0; i < steps; i++) {
    if (millis() - startTime > EMERGENCY_TIMEOUT) {
      analogWrite(3, 0);  // put output in safe state
      return;
    }
    Setpoint = highSetpoint;
    delay(sampleTime);
    Setpoint = lowSetpoint;
    delay(sampleTime);
  }

  //calculate Ku and Pu
  double deltaInput = Input - lastInput;
  if (fabs(deltaInput) < 0.001) {
    deltaInput = 0.001;  // prevent divide-by-zero
  }
  Ku = (4 * (highSetpoint - lowSetpoint)) / (3.14 * deltaInput);
  Pu = (sampleTime * steps) / deltaInput;

  //calculate Kp, Ki, and Kd
  Kp = 0.6 * Ku;
  Ki = 2 * Kp / Pu;
  Kd = Kp * Pu / 8;

  //set PID parameters
  myPID.SetTunings(Kp, Ki, Kd);
}
