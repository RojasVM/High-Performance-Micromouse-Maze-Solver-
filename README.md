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

```text
       [ 7.4V LiPo BATTERY ]
              |      |
            (Red)  (Black)
              |      |
          [ SWITCH ] |
              |      |
              v      v
      +----------------------+          +-------------------------+
      |     ARDUINO NANO     |          |   TB6612FNG DRIVER      |
      |                  VIN | <--(Red)-| VM (Motor Power)        |
      |                  GND | --(Blk)->| GND                     |
      |                   5V | --(Red)->| VCC (Logic Power)       |
      |                      |          | STBY (Connect to 5V)    |
      |                   D3 | -------->| PWMA                    |
      |                   D4 | -------->| AIN1                    |
      |                   D5 | -------->| AIN2                    |
      |                   D7 | -------->| BIN1                    |
      |                   D8 | -------->| BIN2                    |
      |                   D9 | -------->| PWMB                    |
      |                      |          |                         |
      |                      |          | AO1 / AO2 --> [L MOTOR] |
      |                      |          | BO1 / BO2 --> [R MOTOR] |
      +----------------------+          +-------------------------+

         [ SENSORS (VL53L0X) ]
         |  VCC -> 5V        |
         |  GND -> GND       |
         |  SDA -> A4        |
         |  SCL -> A5        |
         |  XSHUT -> D10/11/12|
         +-------------------+
```
## Software & Logic

The intelligence of the robot relies on two main components:
1. PID Controller (Stability)

To keep the robot perfectly centered between walls without zigzagging, a PID (Proportional-Integral-Derivative) control loop corrects the motor speeds in real-time based on sensor error.

$$ Output = K_p \cdot e(t) + K_d \cdot \frac{de}{dt} + K_i \cdot \int e(t) dt $$
2. Navigation (Flood Fill Algorithm)

The robot treats the maze as a grid.

    Exploration Mode: The robot traverses the maze, marking walls and assigning "distance values" to each cell relative to the center.

    Fast Run: Once the center is found, the robot calculates the optimal path and executes a high-speed run.

## Roadmap

    [x] Define Hardware Bill of Materials (BOM).

    [x] Design Circuit Diagram / Schematic.

    [ ] 3D Model the Chassis.

    [ ] Assemble Electronics on Breadboard for testing.

    [ ] Implement Basic Motor Control (Forward/Turn).

    [ ] Implement PID Wall Following.

    [ ] Implement Flood Fill Maze Solving Logic.

## Contributing

This project is open source! Suggestions and pull requests are welcome.
License

Distributed under the MIT License.
