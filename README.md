# Multi-sensor-object-detection-esp32
Beginner-level ESP32 project using multiple sensors to detect obstacles and trigger alerts. Built while exploring embedded systems and sensor interfacing.
This is a beginner-level embedded systems project built using ESP32 and multiple sensors to detect nearby objects and trigger an alert using a buzzer.

I developed this project while experimenting with sensor interfacing and real-time detection logic.

Features
Detects objects using multiple sensors
Works with IR sensors (real hardware) or ultrasonic sensors (simulation)
Buzzer alert when object is detected
Displays which sensor detected the object
Clean logic to avoid repeated alerts.

concept :
The system continuously monitors all sensors.
If any sensor detects an object within a threshold:
A buzzer is triggered
Serial Monitor displays detection message
Also indicates which sensor detected the object

Components Used :
ESP32
IR Sensors (or Ultrasonic sensors in simulation)
HC-SR04 Ultrasonic Sensor
Buzzer
Breadboard & Jumper wires

Simulation : https://wokwi.com/projects/459842431322423297
Since IR sensors are not available in Wokwi, the project was simulated using multiple ultrasonic sensors.
