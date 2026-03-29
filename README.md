# Multi-sensor-object-detection
ESP32 project using multiple sensors to detect obstacles with their distance and trigger alerts. Built while exploring embedded systems and sensor interfacing.
This is an embedded systems project built using ESP32 and multiple sensors to detect nearby objects and their and trigger an alert using a buzzer.

I developed this project while experimenting with sensor interfacing and real-time detection logic.

Features
Detects objects and its distance using multiple sensors 
Works with 3 IR sensors and ultrasonic sensor
Buzzer alert when object is detected
Displays which sensor detected the object.
Additionally,the ultrasonic sensor measures distance and detects object with 20 cm.
Shows all these data in a dashboard.

concept :
The system continuously monitors all sensors.
If any ir sensor detects an object within a threshold:
A buzzer is triggered
Serial Monitor displays detection message with which sensor detected the object and the distance.
A dashboard also shows all these data.

Components Used :
ESP32
IR Sensors 
HC-SR04 Ultrasonic Sensor
Buzzer

Simulation : https://wokwi.com/projects/459842431322423297
Since IR sensors are not available in Wokwi, the project was simulated using multiple ultrasonic sensors.
