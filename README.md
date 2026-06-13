# ESP32-Arduino I2C Sensor Hub

A multi-microcontroller embedded system demonstrating **I2C communication between ESP32 and Arduino Uno** with real-time sensor monitoring and OLED visualization.

The ESP32 works as the central controller, collecting ultrasonic sensor data from an Arduino slave device and displaying the processed output on an SSD1306 OLED display.

---

## Project Overview

This project demonstrates a distributed embedded architecture where multiple microcontrollers communicate over a shared bus.

- ESP32 acts as the I2C Master
- Arduino Uno acts as the I2C Slave
- HC-SR04 ultrasonic sensor provides distance measurements
- SSD1306 OLED displays live sensor data

---

## System Architecture

```text
                 I2C BUS
                    |
                 ESP32
              (I2C Master)
               /        \
              /          \
   SSD1306 OLED       Arduino Uno
    Display           (I2C Slave)
                         |
                      HC-SR04
                  Ultrasonic Sensor
```

---

## Hardware Components

| Component | Purpose |
|---------|---------|
| ESP32 Development Board | Main controller / I2C Master |
| Arduino Uno | Sensor node / I2C Slave |
| HC-SR04 Ultrasonic Sensor | Distance measurement |
| SSD1306 OLED Display | Real-time data visualization |
| Jumper Wires | Connections |

---

## Communication Protocol

### I2C Bus

The project uses I2C for communication between devices.

### ESP32 Connections

| Signal | ESP32 Pin |
|-|-|
| SDA | GPIO 21 |
| SCL | GPIO 22 |

### Arduino Uno Connections

| Signal | Arduino Pin |
|-|-|
| SDA | A4 |
| SCL | A5 |

Arduino slave address:

```cpp
0x08
```

---

## Repository Structure

```text
ESP32-Arduino-I2C-Sensor-Hub/

├── ESP32_Master/
│   ├── main.py
│   └── ssd1306.py
│
├── Arduino_Slave/
│   └── ultrasonic_slave.ino
│
├── docs/
│   └── images/
│
└── README.md
```

---

## ESP32 Master

Responsible for:

- Initializing I2C communication
- Requesting data from Arduino slave
- Processing received sensor values
- Controlling SSD1306 OLED display


Example received data format:

```text
DIST:25
```

Output:

```text
Distance: 25 cm
```

---

## Arduino Slave

Responsible for:

- Reading HC-SR04 ultrasonic sensor values
- Processing echo timing
- Converting readings into centimeters
- Sending formatted data through I2C

---

## SSD1306 OLED Driver

The project includes a MicroPython SSD1306 device driver.

Features:

- OLED initialization
- I2C command transfer
- Frame buffer handling
- Text rendering support

---

## Data Flow

```text
HC-SR04
   |
   v
Arduino Uno
(I2C Slave)
   |
   | DIST:value
   v
ESP32
(I2C Master)
   |
   v
SSD1306 OLED
```

---

## Skills Demonstrated

- Embedded systems development
- Microcontroller communication
- I2C protocol implementation
- Sensor interfacing
- Device driver integration
- MicroPython programming
- Arduino programming

---

## Future Improvements

- Add multiple sensor nodes
- Implement FreeRTOS tasks on ESP32
- Add WiFi dashboard monitoring
- Cloud-based data logging
- PCB implementation

