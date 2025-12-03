# High-Performance-Micromouse-Maze-Solver-
# High-Performance Micromouse Maze Solver

![Status](https://img.shields.io/badge/Status-In_Development-yellow) ![License](https://img.shields.io/badge/License-MIT-blue)

## About The Project
This repository documents the design and construction of an autonomous maze-solving robot built for the **Micromouse** competition standards. The robot is designed to map a maze using the **Flood Fill Algorithm** and navigate the shortest path to the center autonomously.

My goal is to learn embedded systems, PCB design, and control theory (PID) through this hands-on engineering challenge.

## Hardware Specifications
The robot is built around a compact, high-performance architecture:

* **Microcontroller:** Arduino Nano (ATmega328P) for low-level control.
* **Motors:** 2x N20 Micro Metal Gearmotors (600RPM, 6V) for high torque-to-weight ratio.
* **Motor Driver:** TB6612FNG Dual Motor Driver (High efficiency, low heat dissipation).
* **Sensors:** 3x VL53L0X Time-of-Flight (ToF) Laser Distance Sensors (or 5-channel IR Array) for millimeter-precision wall detection.
* **Power:** 7.4V LiPo Battery (2S) for consistent power delivery.
* **Chassis:** Custom 3D printed compact design.

## Software & Algorithms
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
