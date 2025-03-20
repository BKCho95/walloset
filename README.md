# Motor Control System for Raspberry Pi

## Overview
This project is a motor control system for Raspberry Pi using the WiringPi library. The system controls six motors and reads encoder feedback to adjust movement using a PID control loop. The program allows the user to select a storage position, and the motors move accordingly in the x, y, and z axes.

## Features
- Uses **WiringPi** library for GPIO control.
- Controls **6 motors** (MOTOR1 - MOTOR6) with **PWM**.
- Reads encoder feedback from **6 encoders** (ENCODERA - ENCODERF).
- Implements **PID control** for precise motor movement.
- Logs motor positions and velocities to files for analysis.

## Components Used
- **Raspberry Pi** (GPIO-based control)
- **DC motors** with **PWM control**
- **Encoders** for position feedback
- **WiringPi Library** for GPIO handling

## Prerequisites
Ensure you have the following installed on your Raspberry Pi:

```sh
sudo apt update
sudo apt install wiringpi
```

## Wiring Setup
| Motor | GPIO Pin |
|--------|------------|
| MOTOR1 | 18 |
| MOTOR2 | 23 |
| MOTOR3 | 12 |
| MOTOR4 | 16 |
| MOTOR5 | 19 |
| MOTOR6 | 25 |

| Encoder | GPIO Pin |
|--------|------------|
| ENCODERA | 24 |
| ENCODERB | 25 |
| ENCODERC | 20 |
| ENCODERD | 21 |
| ENCODERE | 5 |
| ENCODERF | 6 |

## How to Compile and Run
### **Compile the program:**
```sh
gcc -o motor_control motor_control.c -lwiringPi -lm
```

### **Run the program:**
```sh
sudo ./motor_control
```

## How It Works
1. The user is prompted to select a storage position (1-35).
2. The corresponding x, y, and z positions and motion times are set.
3. Encoders track motor positions and compute the error from the reference position.
4. PID control adjusts the PWM signals to move the motors accordingly.
5. The program logs motion data into files:
   - `/home/pi/Desktop/test/matlab/x_axis.txt`
   - `/home/pi/Desktop/test/matlab/y_axis.txt`
   - `/home/pi/Desktop/test/matlab/z_axis.txt`

## File Logging Format
Each log file contains:
```
Time(ms)   Position (rev)   Velocity (rev/s)
```

## Notes
- Make sure **WiringPi** is installed.
- The program requires **root permissions** to access GPIO.
- The PID parameters (**PGAIN, IGAIN, DGAIN**) can be tuned for better performance.
- Motor movement duration (xtime, ytime, ztime) is predefined for each storage location.

## License
This project is open-source and can be modified for personal or academic use.

## Author
This code was originally developed for a Raspberry Pi motor control system. If you have any questions, feel free to ask!
