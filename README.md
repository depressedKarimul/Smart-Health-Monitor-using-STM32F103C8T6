# Smart Health Monitor using STM32F103C8T6

## 1. Introduction

This project presents a **Smart Health Monitoring System** using the STM32F103C8T6 (Blue Pill) microcontroller. The system utilizes a **MAX30100 pulse oximeter sensor** to measure heart rate and SpO₂ levels, a **DS18B20 temperature sensor** for body temperature measurement, and a **16x2 LCD** for displaying results. The display dynamically switches between sensors based on touch detection and readings.

---

## 2. Components Used

- STM32F103C8T6 (Blue Pill)
- MAX30100 Pulse Oximeter and Heart Rate Sensor
- DS18B20 Temperature Sensor Module
- 16x2 LCD Display
- ST-Link V2 Programmer
- Jumper wires, Breadboard, Power Supply

---

## 3. Circuit Diagram

The schematic below shows the wiring between the STM32 board, MAX30100, DS18B20, and LCD display:

![Circuit Diagram](https://i.postimg.cc/3NJwPWTV/Screenshot-2025-04-21-223348.png)

---

## 4. Pin Configuration

### LCD (16x2):
- RS: PA0  
- E: PA1  
- D4: PA2  
- D5: PA3  
- D6: PA4  
- D7: PA5  

### MAX30100:
- VIN: 3.3V  
- GND: GND  
- SDA: PB7  
- SCL: PB6  

### DS18B20:
- VCC: 3.3V or 5V  
- GND: GND  
- DATA: PB0 (with 4.7kΩ pull-up resistor to VCC)

---

## 5. Final Project

Final assembled project image:

![Final Project](https://i.postimg.cc/VvSxrcB5/Whats-App-Image-2025-04-22-at-21-44-57-c6466bb7.jpg)

---

## 6. Code

The complete code for the project is available in the `SmartHealthMonitor.ino` file. It handles sensor initialization, data reading, and dynamic display.

---

## 7. Prices of the Components

| Components                                | Price (BDT) |
|-------------------------------------------|-------------|
| STM32F103C8T6 (Blue Pill)                 | 490.00      |
| MAX30100 Pulse Oximeter and Heart Sensor | 378.00      |
| DS18B20 Temperature Sensor Module         | 150.00      |
| 16x2 LCD Display                          | 255.00      |
| ST-Link V2 Programmer                     | 435.00      |
| Lithium Polymer Battery                   | 329.00      |
| Jumper wires, Breadboard, Soldering       | 800.00      |

---

## 8. Software and Tools Used

- Arduino IDE (with STM32 board support)
- STM32CubeProgrammer (for uploading via ST-Link)
- Required Libraries:
  - `Wire`
  - `LiquidCrystal`
  - `MAX30100_PulseOximeter`
  - `OneWire`
  - `DallasTemperature`

---

## 9. Working Principle

- The system initializes all sensors and the LCD on boot.
- When a finger is placed on the MAX30100 sensor, the LCD displays **Heart Rate** and **SpO₂** readings.
- If the DS18B20 detects a temperature in the human range (20°C–50°C), it switches the LCD to display **temperature**.
- If no readings are detected for 5 seconds, the screen returns to **idle mode** with instructions.

---

## 10. Conclusion

This **Smart Health Monitor** provides a simple yet effective method to track vital signs in real time. It integrates multiple sensors and offers a responsive interface, making it ideal for **wearable or portable health-monitoring applications**.

---
