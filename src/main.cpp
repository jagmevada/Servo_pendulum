#include <Arduino.h>
#include <Servo.h>

Servo myservo;

const int servoPin = 9;

// === Pendulum Settings ===
float thetaMax = 45.0;      // Maximum swing angle (degrees)
float period = 3.0;         // Total period of the swing (seconds)
unsigned long startTime;

void setup() {
  myservo.attach(servoPin);
  startTime = millis();
}

void loop() {
  float t = (millis() - startTime) / 1000.0; // time in seconds

  // Calculate pendulum angle based on sine wave
  float angle = thetaMax * sin((2 * PI / period) * t);

  // Servo.write() takes angles from 0 to 180; map -θ to +θ into servo range
  float servoAngle = 90 + angle; // Centered at 90°

  myservo.write(servoAngle);
  delay(20); // Refresh rate ~50 Hz
}
