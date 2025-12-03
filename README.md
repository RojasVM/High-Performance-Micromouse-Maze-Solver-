# MazeRunner: High-Performance Micromouse

![Status](https://img.shields.io/badge/Status-In_Development-yellow) ![License](https://img.shields.io/badge/License-MIT-blue) ![Platform](https://img.shields.io/badge/Platform-Arduino-teal)

## Project Overview
This repository documents the engineering process of building an autonomous maze-solving robot based on **Micromouse** competition standards. The goal is to create a compact robot capable of mapping an unknown maze and calculating the shortest path to the center using the **Flood Fill Algorithm**.

This project allows me to explore advanced concepts in embedded systems, sensor fusion, and real-time control theory.

---

## Hardware Bill of Materials (BOM)
I have selected high-efficiency components to ensure speed and precision:

| Component | Specification | Purpose |
| :--- | :--- | :--- |
| **Microcontroller** | Arduino Nano (ATmega328P) | Central processing unit for logic and control. |
| **Motors** | 2x N20 Micro Metal Gearmotors (6V, 600RPM) | High torque-to-weight ratio for quick acceleration. |
| **Motor Driver** | TB6612FNG Dual Driver | More efficient H-Bridge than the standard L298N (less voltage drop). |
| **Sensors** | 3x VL53L0X Time-of-Flight (ToF) | Laser distance measurement for millimeter-precision wall detection. |
| **Power** | 7.4V LiPo Battery (2S) | High current discharge for motors. |
| **Chassis** | Custom 3D Printed | Lightweight structure designed in CAD. |

---

## Wiring Diagram
*Auto-generated system architecture using Mermaid.js:*

```mermaid
graph TD
    %% Node Styles
    classDef pwr fill:#f96,stroke:#333,stroke-width:2px;
    classDef micro fill:#3178C6,stroke:#333,stroke-width:2px,color:white;
    classDef driver fill:#ff9,stroke:#333,stroke-width:2px;
    classDef motor fill:#ddd,stroke:#333,stroke-width:2px;
    classDef sensor fill:#9f9,stroke:#333,stroke-width:2px;

    %% Components
    Bat[7.4V LiPo Battery]:::pwr
    Switch[Power Switch]:::pwr
    Nano[Arduino Nano]:::micro
    Driver[TB6612FNG Driver]:::driver
    MotL[Left Motor N20]:::motor
    MotR[Right Motor N20]:::motor
    Sensors[3x VL53L0X Sensors]:::sensor

    %% Power Connections
    Bat -->|GND| Nano
    Bat -->|GND| Driver
    Bat -->|GND| Sensors
    Bat -->|V+ 7.4V| Switch
    Switch -->|VIN| Nano
    Switch -->|VM Motor Pwr| Driver
    Nano -->|5V Out| Driver
    Nano -->|5V Out| Sensors

    %% Control Signals
    Nano -->|PWM/Dir D3, D4, D5| Driver
    Nano -->|PWM/Dir D9, D7, D8| Driver
    Driver -->|Output A| MotL
    Driver -->|Output B| MotR

    %% Sensor Communication
    Sensors -->|I2C SDA/SCL| Nano
    Sensors -->|XSHUT D10, D11, D12| Nano

## Software & Logic
The intelligence of the robot relies on two main components:

1.  **PID Controller:** Ensures the robot moves in a perfectly straight line and stays centered between walls by constantly correcting motor speed based on sensor error.
2.  **Flood Fill Algorithm:**
    * **Exploration Mode:** The robot traverses the maze, updating a virtual map in memory to mark walls and open paths.
    * **Fast Run:** Once the center is found, the robot calculates the optimal path and executes a high-speed run.

## Roadmap
- [x] Define Hardware Bill of Materials (BOM).
- [x] Design Circuit Diagram / Schematic.
- [ ] 3D Model the Chassis.
- [ ] Assemble Electronics on Breadboard for testing.
- [ ] Implement Basic Motor Control (Forward/Turn).
- [ ] Implement PID Wall Following.
- [ ] Implement Flood Fill Maze Solving Logic.

## Contributing
This project is open source! Suggestions and pull requests are welcome.

## License
Distributed under the MIT License.
