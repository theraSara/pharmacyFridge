# Pharmacy Fridge Monitoring System

This project is a pharmacy fridge monitoring system designed to ensure that medications are stored at safe temperatures. The system uses sensors to monitor temperature levels and employs a state machine to classify the fridge's temperature state. Based on the classification, the system provides feedback via a buzzer, LED, and motor control.

---

## Features

- **Temperature Monitoring**: Reads temperatures from multiple sensors (`DangWarmTempPIN`, `WarmTempPIN`, `NormalTempPIN`).
- **Classification System**: Implements an SVM-based classifier to determine the temperature state:
  - `Normal`
  - `Warm`
  - `Dangerously Warm`
- **Alerts and Control**:
  - Activates a buzzer and LED for warnings.
  - Adjusts motor speed to maintain optimal conditions or discard compromised medications.
- **Stop Button Integration**: Provides a manual stop function for emergency handling.

---

## System States

1. **Idle**: Initializes the system.
2. **CollectX**: Collects temperature readings from sensors.
3. **Classify**: Classifies the temperature state using the SVM algorithm.
4. **TempState**: Executes appropriate actions based on the classified temperature state.

---

## How It Works

- **Normal State**: The fridge operates normally at full motor speed with no alerts.
- **Warm State**: The system issues a warning via a buzzer and LED while reducing motor speed.
- **Dangerously Warm State**: The system alerts the user, reduces motor speed significantly, and discards compromised medications if required.

---

## Hardware Requirements

- Microcontroller (e.g., Arduino)
- Temperature sensors (connected to `A1`, `A2`, `A3`)
- Buzzer (connected to `A0`)
- LED (connected to pin `10`)
- Motor (connected to pin `9`)
- Stop push button (connected to pin `11`)

---

## Setup

1. Connect the hardware components as specified.
2. Upload the provided code to the microcontroller.
3. Monitor the system's status via the serial monitor.

---

## Note

This project is a class assignment prototype for demonstrating concepts in temperature monitoring, classification, and automated control. Further optimization may be required for real-world deployment.

---
