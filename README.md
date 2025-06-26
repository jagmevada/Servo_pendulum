# 🕰️ Arduino Sinusoidal Pendulum Servo

This project simulates a natural pendulum swing using a servo motor, controlled by an Arduino. Unlike traditional linear movement, this pendulum moves sinusoidally—just like a real one—providing smooth acceleration and deceleration at the ends of its swing.

## 📷 Overview

The servo oscillates between ±θ (e.g., ±45°) with a configurable **swing period** (e.g., 3 seconds for a full cycle). The motion is modeled as:
```
θ(t) = θ_max × sin(2πt / T)
```

## 🔧 Hardware Required

- Arduino Nano / Uno / Mega / ESP32 / etc.
- Servo Motor (e.g., SG90 or MG995)
- Jumper wires
- (Optional) Potentiometer or keypad for runtime period/angle control

## 🧠 Features

- **Natural pendulum motion** using `sin()` function
- **Adjustable swing period**
- Clean center-aligned swing (`90 ± θ`)
- Easy integration of live input controls

## 📜 Arduino Sketch

```cpp
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


## 🔄 Customization

- Change `thetaMax` to adjust swing amplitude.
- Modify `period` to slow down or speed up the swing.
- You can dynamically update values using:
  - A **potentiometer** connected to an analog pin.
  - A **keypad** or **serial input**.

## 📝 Notes

- Servo resolution and jitter may limit precision for small swing amplitudes.
- For best effect, center the physical setup to match 90° neutral servo angle.



## 📷 Demo

> *(Optional: Add GIF or video link showing servo swinging smoothly)*

---

Made with ❤️ using Arduino and trigonometry.
