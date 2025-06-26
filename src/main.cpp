#include <Arduino.h>
#include <Servo.h>

Servo myservo;

const int servoPin = 9;

// === Pendulum Settings ===
float thetaMax = 22.5;         // Half of total swing angle (45° total)
float meanAngle = 80.0;        // Center position (mid-swing)
float period = 0.6;            // Total period of full swing (seconds)
unsigned long startTime;

// === Servo Pulse Parameters ===
const int minPulse = 550;      // microseconds at 0°
const int maxPulse = 2200;     // microseconds at 160°
const float angleMin = 0.0;
const float angleMax = 160.0;

void setup() {
  myservo.attach(servoPin);

  // Get current position (assume 0 for safe start)
  float currentAngle = 80.0;

  // Smoothly move to meanAngle (80°)
  while (currentAngle < meanAngle) {
    int pulse = map(currentAngle, angleMin, angleMax, minPulse, maxPulse);
    myservo.writeMicroseconds(pulse);
    currentAngle += 1.0;
    delay(15);  // Adjust speed of ramp-up
  }

  startTime = millis(); // Begin swing timer
}

void loop() {
  float t = (millis() - startTime) / 1000.0;  // Time in seconds

  // Sinusoidal angle: swings around meanAngle ± thetaMax
  float angle = meanAngle + thetaMax * sin((2 * PI / period) * t);

  // Convert angle to pulse
  int pulse = map(angle, angleMin, angleMax, minPulse, maxPulse);
  myservo.writeMicroseconds(pulse);

  delay(20);  // ~50 Hz refresh
}
