#include "DabbleESP32.h"

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

// Motor driver pins
const int motor1DirPin = 14;
const int motor1PwmPin = 32;
const int motor2DirPin = 27;
const int motor2PwmPin = 13;
const int motor3DirPin = 26;
const int motor3PwmPin = 12;
const int motor4DirPin = 25;
const int motor4PwmPin = 33;

// PWM setup
const int pwmFreq = 5000;
const int pwmResolution = 8;
const int maxSpeed = 255;

void setup() {
  Serial.begin(115200);
  Dabble.begin("SoccerBot");

  pinMode(motor1DirPin, OUTPUT);
  pinMode(motor2DirPin, OUTPUT);
  pinMode(motor3DirPin, OUTPUT);
  pinMode(motor4DirPin, OUTPUT);

  // Setup PWM channels
  ledcSetup(0, pwmFreq, pwmResolution);
  ledcSetup(1, pwmFreq, pwmResolution);
  ledcSetup(2, pwmFreq, pwmResolution);
  ledcSetup(3, pwmFreq, pwmResolution);

  // Attach PWM pins
  ledcAttachPin(motor1PwmPin, 0);
  ledcAttachPin(motor2PwmPin, 1);
  ledcAttachPin(motor3PwmPin, 2);
  ledcAttachPin(motor4PwmPin, 3);
}

void setMotor(int dirPin, int channel, int speed) {
  if (speed >= 0) {
    digitalWrite(dirPin, HIGH);
    ledcWrite(channel, speed);
  } else {
    digitalWrite(dirPin, LOW);
    ledcWrite(channel, -speed);
  }
}

void loop() {
  Dabble.processInput();

  int x = GamePad.getXaxisData();   // -7 to +7
  int y = GamePad.getYaxisData();   // -7 to +7
  int w = (GamePad.isSquarePressed()) ? 5 : 0; // example for rotation

  // Scale to 255
  x = map(x, -7, 7, -maxSpeed, maxSpeed);
  y = map(y, -7, 7, -maxSpeed, maxSpeed);

  // Omniwheel calculations
  int m1 = y + x + w;
  int m2 = y - x - w;
  int m3 = y - x + w;
  int m4 = y + x - w;

  // Send to motors
  setMotor(motor1DirPin, 0, m1);
  setMotor(motor2DirPin, 1, m2);
  setMotor(motor3DirPin, 2, m3);
  setMotor(motor4DirPin, 3, m4);
}
