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
float thetaMax = 45.0;      // Max swing angle (degrees)
float period = 3.0;         // Total swing period (seconds)
unsigned long startTime;

void setup() {
  myservo.attach(servoPin);
  startTime = millis();
}

void loop() {
  float t = (millis() - startTime) / 1000.0; // time in seconds

  // Calculate pendulum angle as a sine function
  float angle = thetaMax * sin((2 * PI / period) * t);

  // Map angle to servo range (centered at 90°)
  float servoAngle = 90 + angle;
  myservo.write(servoAngle);

  delay(20); // Update at ~50 Hz
}
```

## 🔄 Customization

- Change `thetaMax` to adjust swing amplitude.
- Modify `period` to slow down or speed up the swing.
- You can dynamically update values using:
  - A **potentiometer** connected to an analog pin.
  - A **keypad** or **serial input**.

## 📝 Notes

- Servo resolution and jitter may limit precision for small swing amplitudes.
- For best effect, center the physical setup to match 90° neutral servo angle.

## 📁 File Structure

```
/SinusoidalPendulum/
│
├── SinusoidalPendulum.ino   // Main Arduino sketch
└── README.md                // Project documentation
```

## 📷 Demo

> *(Optional: Add GIF or video link showing servo swinging smoothly)*

---

Made with ❤️ using Arduino and trigonometry.
