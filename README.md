# ESPinsp
The purpose of this little ESP32 project is to simply play a pre-recorded mp3 soundtrack, using a normal stereo with an audio plug, when motion is detected with a PIR (motion) sensor.

## Hardware
- ESP32 <https://i.ibb.co/BKn4dgL/ESP32-DEV-CP2102-C-003.jpg>
- PIR motion sensor <https://whadda.com/product/pir-motion-sensor-wpse314/>
- Stereo

## PINS
Stereo left is the tip of the audio plug. Right is the middle part and ground is the base.
| Device       | ESP32         |
| -------------|:-------------:| 
| PIR VCC      | 5V            |
| PIR out      | GPIO16        |
| PIR GND      | GND           |
| Stereo left  | GPIO25 DAC    |
| Stereo right | GPIO26 DAC    |
| Stereo GND   | GND           |

## Install
Follow this installation guide, or use your favorite tools for ESP32 programming. The library dependencies are
- Arduino-audio-tools <https://github.com/pschatzmann/arduino-audio-tools>
- arduino-libhelix <https://github.com/pschatzmann/arduino-libhelix?tab=readme-ov-file>

Install `arduino-cli` <https://arduino.github.io/arduino-cli/1.1/installation/>

Clone the libraries under `Arduino/libraries` or use your favorite method for managing dependencies.
```
cd ~/Arduino/libraries
git clone https://github.com/pschatzmann/arduino-libhelix.git
git clone https://github.com/pschatzmann/arduino-audio-tools.git
```

Intalling libraries with arduino-cli
```
arduino-cli lib install --git-url https://github.com/me-no-dev/AsyncTCP.git https://github.com/me-no-dev/ESPAsyncWebServer.git
```

## Usage
Plug your ESP32. Now you should see with `sudo dmesg` that the ESP32 has been connected as well as the serialport it has been connected to, e.g. `/dev/ttyUSB0`. If you are a good citizen, you should have a udev rule for your device that ensures the correct permissions for your port. But in case you are not, you can get your permissions with `sudo chown $USER <port>`.

After noting down the port, and ensuring that you have read/write access to it, you can\
`make all` to compile & run

or alternatively
`make compile` for compiling the project
`make upload` for writing the program to ESP32

Then you can monitor the serial communication using arduino-cli
```
arduino-cli monitor -p <your serial port, e.g. /dev/ttyUSB0> --config <baud-rate, 115200 in this project>
```
