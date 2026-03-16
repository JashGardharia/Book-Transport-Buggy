# Components Required
## Book Transport Buggy

This document lists the hardware components required to build the autonomous Book Transport Buggy designed to carry and deliver books within a school corridor.

---

# 1. Main Controller

- 1 × ESP32 Development Board

Purpose  
Acts as the central controller of the robot. Handles WiFi communication, navigation logic, and motor control.

---

# 2. Vision System

- 1 × ESP32-CAM Module

Purpose  
Provides real-time camera vision for monitoring and navigation. Can be used for remote observation or future AI-based navigation improvements.

---

# 3. Navigation Sensor

- 1 × LiDAR Sensor (e.g., LD06 / TFmini / similar)

Purpose  
Used for corridor mapping and obstacle detection. Helps the robot understand distance from walls and objects.

---

# 4. Motor Driver

- 1 × L298N Motor Driver Module

Purpose  
Controls the speed and direction of the drive motors.

---

# 5. Drive Motors

- 2 × N20 Metal Gear Motors

Purpose  
Provides strong torque required to move the buggy while carrying up to 50 books.

---

# 6. Wheels and Chassis

- 2 × High traction wheels
- 1 × Caster wheel
- 1 × Metal or acrylic robot chassis

Purpose  
Provides the structural base and mobility of the buggy.

---

# 7. Book Storage Platform

- Flat storage tray
- Side support walls
- Anti-slip surface

Purpose  
Holds and stabilizes books during transportation.

---

# 8. Power System

- 2 × 18650 Li-ion Batteries
- 1 × Battery Holder
- 1 × Power Switch

Purpose  
Supplies power to the entire system.

---

# 9. Voltage Regulation

- 1 × LM2596 Buck Converter

Purpose  
Regulates battery voltage to stable 5V for ESP32 and camera module.

---

# 10. Wireless Control

- WiFi communication via ESP32
- Mobile application built using MIT App Inventor

Purpose  
Allows teachers to call the buggy to a specific classroom through the mobile app.

---

# 11. Indicators (Optional)

- 1 × Status LED
- 1 × Buzzer

Purpose  

LED → system status indicator  
Buzzer → arrival notification

---

# 12. Basic Electronics

- Breadboard or PCB
- Jumper wires
- Resistors (220Ω)
- Mounting brackets
- Screws and nuts

Purpose  
Used for circuit connections and mechanical assembly.

---

# Component Summary

| Category | Components |
|--------|------------|
| Controller | ESP32 |
| Vision | ESP32-CAM |
| Navigation | LiDAR Sensor |
| Motor Driver | L298N |
| Drive System | N20 Metal Gear Motors |
| Power | 18650 Batteries |
| Voltage Regulation | Buck Converter |
| Structure | Chassis, wheels, book tray |

---

# Notes

The LiDAR sensor is used to map the corridor and detect obstacles. The robot navigates based on stored route data and receives destination commands from the mobile application.

Ensure that all modules share a common ground for stable operation. 
