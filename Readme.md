# RetroConnect: Retrofit Telephone 
![RetroConnect Phone](/Wiring/PXL_20231207_034615249.jpg "RetroConnect Phone")

## Description
The Internet-Connected Retro Telephone is a project born out of a fascination with IoT and telecommunication. The motivation behind this endeavor is to explore the rapid evolution of technology and the stark differences in devices used over the past decades. By repurposing an old telephone, the project aims to showcase the transformative journey from traditional rotary dial phones to modern smart IoT devices. Additionally, it delves into the emergence of wireless technology, filling our surroundings with invisible data flows.

The project itself is a retrofit telephone equipped with up-to-date WiFi technology, serving as an interpreter of the invisible data flow around us. Users can connect to the internet using this device, experiencing the blend of old and new technologies. The telephone generates different characters and beeps at varying frequencies based on the delay of accessing websites. WiFi connectivity is provided through an ESP 8266 WiFi module connected to the Arduino, while character display is achieved using a 1602 Serial enabled LCD. Beeping and key input are facilitated through the telephone's original keypad and speaker.

## Table of Contents
- [Schematic](#schematic)
- [Installation](#installation)
- [Usage](#usage)

## Schematic
![Wiring Breadboard View](/Wiring/Wiring_bb.png "Wiring in Breadboard View")
![Wiring Schematic View](/Wiring/Wiring_schem.png "Wiring in Shematic View")
The two 10 pin connectors are the key connector from the telephone, the key mapping can be found in the __Phone Key test.xlsx__ file. Wires are in the same order in the breadboard graph and the actual connector, both from left to right. The 4 pin connector is the telephone's speaker & mic connector, also preserved the original color in the breadboard view. 
![Key Connector](/Wiring/Wiring.jpg "Key Connector Graph")

## Installation Notes
Some important notes to make the phone work properly

- Connect the ESP 8266 WIFI module to the Arduino and run the ``ESP 8266 Setup.ino`` file once to set the default baud rate to 9600, 115200 is too fast for stable communication.
- When developing, do not send too many commands at once to the ESP 8266, add delays between commands
- The ``lcd.clear()`` function in the SerLCD library is not working properly so print spaces (" ") to clear the screen.
- Careful about the external reset button, especially when flipped the PCB board. Make sure the Arduino is not resetting infinitely.

## Usage
Once installed, RetroConnect can be used to connect to the internet and access websites. Users can input URLs using the original telephone keypad, and the device will respond with characters and beeps corresponding to the site's delay. This unique interaction aims to make users reflect on the evolution of technology while experiencing the charm of vintage communication devices.