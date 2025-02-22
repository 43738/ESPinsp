compile:
	arduino-cli compile --fqbn esp32:esp32:nodemcu-32s ESPinsp.ino
upload:
	arduino-cli upload -p /dev/ttyUSB0 --fqbn esp32:esp32:nodemcu-32s ESPinsp.ino

all: compile upload
