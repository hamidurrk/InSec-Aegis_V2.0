# **InSec-Aegis_V2.0**

This is a repository for InSec-Aegis_V2.0, a project that aims to create a secure and intelligent system for home security and automation. It is a system that can follow a line and be controlled remotely by an app. It uses an Arduino Uno board, a camera module, a line following sensor, and a Bluetooth module to create a smart and secure robot. The user can stream video from the robot’s camera to the app and control the robot’s movement using buttons on the app. The robot can also detect and follow a black line on a white surface using the line following sensor. The system is designed for home security and automation purposes.


## **Features**



* UI_ss: This folder contains screenshots of the user interface of the system.
* app file: This folder contains the source code and executable file of the app that controls the system.
* awards: This folder contains certificates and awards that the project has received.
* icon: This folder contains the icon of the app and the system.
* img: This folder contains images of the hardware components and the prototype of the system.
* prototype video: This folder contains a video demonstration of the system in action.
* schematic: This folder contains the schematic diagram of the system’s circuitry and connections.
* src: This folder contains the source code of the system’s firmware.


## **Installation**

To install and run the project, you will need:



* An Arduino Uno board
* A Bluetooth module (HC-05)
* A camera module (OV7670)
* A line following sensor (TCRT5000)
* Two DC motors
* A motor driver (L298N)
* A 3S lipo battery
* A smartphone with Android OS

Follow these steps to install and run the project:



1. Clone this repository to your computer using `git clone https://github.com/hamidurrk/InSec-Aegis_V2.0.git`
2. Connect the hardware components according to the schematic diagrams in the Arduino and Camera folders.
3. Compile and upload the Arduino code in the Arduino folder to your Arduino Uno board using `arduino-cli compile --fqbn arduino:avr:uno InSec-Aegis_V2.0.ino` and `arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno InSec-Aegis_V2.0.ino`.
4. Install the app file in the App folder to your smartphone using `adb install InSec-Aegis_V2.0.apk`.
5. Pair your smartphone with the Bluetooth module using the default password `1234`.
6. Launch the app and select the Bluetooth device to connect to the robot.
7. Enjoy your InSec-Aegis_V2.0!

## **License**

This project is licensed under the MIT License - see the LICENSE file for details.
