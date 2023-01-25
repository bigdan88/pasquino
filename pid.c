#include <PID_v1.h>

double Setpoint, Input, Output;
double Kp, Ki, Kd;

PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  Setpoint = 100;
  Input = analogRead(A0);
  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(100);
  myPID.SetOutputLimits(0, 255);
  pinMode(3, OUTPUT);
  autoTune();
}

void loop() {
  Input = analogRead(A0);
  myPID.Compute();
  analogWrite(3, Output);
}

void autoTune() {
  double highSetpoint = 110;
  double lowSetpoint = 90;
  double Ku, Pu;
  double lastInput = Input;
  int sampleTime = 1000;
  int steps = 30;

  //run relay experiment
  for (int i = 0; i < steps; i++) {
    Setpoint = highSetpoint;
    delay(sampleTime);
    Setpoint = lowSetpoint;
    delay(sampleTime);
  }

  //calculate Ku and Pu
  Ku = (4 * (highSetpoint - lowSetpoint)) / (3.14 * (Input - lastInput));
  Pu = sampleTime * steps / (Input - lastInput);

  //calculate Kp, Ki, and Kd
  Kp = 0.6 * Ku;
  Ki = 2 * Kp / Pu;
  Kd = Kp * Pu / 8;

  //set PID parameters
  myPID.SetTunings(Kp, Ki, Kd);
}