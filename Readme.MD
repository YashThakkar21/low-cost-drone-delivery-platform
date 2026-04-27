# Low-Cost Drone Delivery Platform

A modular, open-source payload delivery add-on for commodity drone platforms. Designed and evaluated as part of an independent work project at Princeton University.

## Overview

This system attaches to an existing drone airframe and autonomously releases a payload when the drone descends to within one foot of the ground, detected via an HC-SR04 ultrasonic sensor. Two door mechanisms are provided and evaluated: a conventional hinged door and a sliding door.

| Mechanism | Success Rate | Servo | Flight Tested |
|---|---|---|---|
| Hinged door | 28% (7/25) | 1× MG996R | No |
| Sliding door | 84% (21/25) | 2× SG90 | Yes (8/10) |

The sliding door is the recommended design.

## Repository Structure

```
low-cost-drone-delivery-platform/
├── written_final_report.pdf    # Full research paper
├── conventional_door.ino       # Arduino firmware for hinged door
├── sliding_door.ino            # Arduino firmware for sliding door
├── payload_cad_files/          # Payload enclosure (upper + lower modules)
├── hinged_door_cad_files/      # Hinged door mechanism CAD
├── sliding_door_cad_files/     # Sliding door mechanism CAD (modified panels)
└── component_mounts_cad_files/ # Arduino/breadboard mount, sensor case
```

## Hardware Requirements

| Component | Quantity |
|---|---|
| Drone with landing gear rails (e.g. Holybro X500 V2) | 1 |
| Arduino Uno | 1 |
| HC-SR04 ultrasonic sensor | 1 |
| SG90 servo motor (sliding door) | 2 |
| MG996R servo motor (hinged door) | 1 |
| 9V battery + connector | 1 |
| PLA filament (for 3D printing) | — |

## Setup

1. **Print** all CAD files in `payload_cad_files/`, `sliding_door_cad_files/`, and `component_mounts_cad_files/` using standard PLA.
2. **Assemble** the two-module enclosure: seat the Arduino and breadboard in the upper module, install the door mechanism in the lower module, and connect via the screw joint.
3. **Wire** the HC-SR04 to Arduino pins 7 (Trig) and 8 (Echo). Connect SG90 servos to pins 9 and 10. Power via 9V battery.
4. **Flash** `sliding_door.ino` to the Arduino using the Arduino IDE.
5. **Mount** the enclosure onto the drone's landing gear arms using the printed rail mount.

The door triggers automatically when the sensor reads ≤ 30.48 cm (1 ft) from the ground and closes after 10 seconds.

## Flight Platform

Any drone capable of carrying the payload system (~1.4 lb) can be used. This project was developed and tested on the **Holybro X500 V2** with a **Pixhawk 6C** running **PX4 firmware**, configured via **QGroundControl**.

## Paper

Full design details, evaluation methodology, and results are available in [`written_final_report.pdf`](./written_final_report.pdf). Topics covered include the iterative CAD design process (7 enclosure versions), bench reliability testing, flight trials, cost analysis, and a comparison against existing commercial and open-source platforms.

## License

Open-source. All CAD files and firmware are free to use, modify, and distribute.

---

*Princeton University — Department of Computer Science — Spring 2026*  
*Advisor: Professor David August*