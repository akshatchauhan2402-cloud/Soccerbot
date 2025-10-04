/*
 * SoccerBot Control Code
 * 
 * This code is designed to control a soccerbot with 4 omniwheels using an
 * ESP32 microcontroller. The bot is powered by a 3S LiPo battery and uses
 * 4 JGB37-520 motors, each controlled by a CYTRON MD10C motor driver. The
 * ESP32 receives commands via Bluetooth using the Dabble app to control
 * the direction and speed of the motors.
 */

#include "DabbleESP32.h"

// Motor driver pins
const int motor1DirPin = 14;
const int motor1PwmPin = 32;
const int motor2DirPin = 27;
const int motor2PwmPin = 13;
const int motor3DirPin = 26;
const int motor3PwmPin = 12;
const int motor4DirPin = 25;
const int motor4PwmPin = 33;

// PWM frequency and resolution
const int pwmFreq = 5000;
const int pwmResolution = 8;

// Motor speed range
const int minSpeed = 0;
const int maxSpeed = 255;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Initialize Dabble
  Dabble.begin("SoccerBot");

  // Set motor pins as outputs
  pinMode(motor1DirPin, OUTPUT);
  pinMode(motor1PwmPin, OUTPUT);
  pinMode(motor2DirPin, OUTPUT);
  pinMode(motor2PwmPin, OUTPUT);
  pinMode(motor3DirPin, OUTPUT);
  pinMode(motor3PwmPin, OUTPUT);
  pinMode(motor4DirPin, OUTPUT);
  pinMode(motor4PwmPin, OUTPUT);

  // Setup PWM channels
  ledcSetup(0, pwmFreq, pwmResolution);
  ledcSetup(1, pwmFreq, pwmResolution);
  ledcSetup(2, pwmFreq, pwmResolution);
  ledcSetup(3, pwmFreq, pwmResolution);

  // Attach PWM channels to pins
  ledcAttachPin(motor1PwmPin, 0);
  ledcAttachPin(motor2PwmPin, 1);
  ledcAttachPin(motor3PwmPin, 2);
  ledcAttachPin(motor4PwmPin, 3);
}

void loop() {
  // Update Dabble
  Dabble.processInput();

  // Get joystick values
  int x = Dabble.getJoystickValue('X');
  int y = Dabble.getJoystickValue('Y');

  // Calculate motor speeds based on joystick input
  int motor1Speed = constrain(y + x, minSpeed, maxSpeed);
  int motor2Speed = constrain(y - x, minSpeed, maxSpeed);
  int motor3Speed = constrain(y - x, minSpeed, maxSpeed);
  int motor4Speed = constrain(y + x, minSpeed, maxSpeed);

  // Set motor directions
  digitalWrite(motor1DirPin, motor1Speed >= 0 ? HIGH : LOW);
  digitalWrite(motor2DirPin, motor2Speed >= 0 ? HIGH : LOW);
  digitalWrite(motor3DirPin, motor3Speed >= 0 ? HIGH : LOW);
  digitalWrite(motor4DirPin, motor4Speed >= 0 ? HIGH : LOW);

  // Set motor speeds
  ledcWrite(0, abs(motor1Speed));
  ledcWrite(1, abs(motor2Speed));
  ledcWrite(2, abs(motor3Speed));
  ledcWrite(3, abs(motor4Speed));
}
