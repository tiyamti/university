# IoT Project: LED Control via Web Interface and AI

## Overview
This project demonstrates an IoT system that controls LEDs through a web interface and integrates AI for natural language processing. It includes:
- An ESP32-based web server for LED control.
- Face recognition for user authentication.
- GPT-3.5 Turbo to convert text commands into control codes.

## Features
- **Web Interface**: Real-time LED status display and command input.
- **AI Integration**: Converts natural language commands (e.g., "turn on LED1") into control signals.
- **Face Recognition**: Ensures only authorized users can operate the system.
- **Serial Communication**: Connects the Python script with the ESP32.

## Hardware Requirements
- ESP32 microcontroller.
- 2 LEDs (connected to pins 33 and 4).
- USB-to-Serial adapter (if needed).

## Software Setup
1. **ESP32 Code**:
   - Upload `PROJECT-IOT.ino` to ESP32 using Arduino IDE.
   - Install required libraries: `WiFi`, `WebServer`, `ArduinoJson`.

2. **Python Script**:
   - Install dependencies:
     ```
     pip install face_recognition opencv-python langchain-openai pyserial
     ```
   - Add known face images to the `known_faces` directory.
   - Update `port_name` in `PROJECT-IOT.py` (e.g., `COM3` or `/dev/ttyUSB0`).
   - Run the script:
     ```
     python PROJECT-IOT.py
     ```

## Usage
1. Connect to the ESP32's Wi-Fi (SSID: `iot`, Password: `123456789`).
2. Open `http://192.168.4.1` in a browser.
3. Enter commands in the text box (e.g., "Please turn on LED1").
4. The system will process the command via GPT and update the LEDs accordingly.

## Contributing
Pull requests are welcome. For major changes, please open an issue first.

## License
[MIT](https://choosealicense.com/licenses/mit/)