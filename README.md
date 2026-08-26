# Arduino Gmod Interface
 Experimental Garry's Mod module that allows the game to communicate with Arduino devices, and vice versa using [SerialPort.](https://github.com/manashmandal/SerialPort) This repo contains the base addon, the binary module, and a Wiremod tool. Currently only works on Windows.

## Installing the Base
 1. Download the latest release from [here.](https://github.com/LambdaGaming/ArduinoGmodInterface/releases)
 2. Copy the folders inside the zip file to `garrysmod/garrysmod/lua`.
 3. Launch the game and you should now be able to use the API and Wiremod tool! If you need help with the API, read the comments above each function in [main.cpp](module/src/main.cpp) and take a look at the [examples.](examples)

## Using the Wiremod Tool
 Ensure you have the base and [Wiremod](https://steamcommunity.com/sharedfiles/filedetails/?id=160250458) downloaded, and an Arduino device plugged into your PC. The Arduino must be programmed to send or receive data through the serial port at a baudrate of 9600.

 The Wiremod tool can be found in the "Chips, Gates" category. Once you have it selected, you can change various settings that include:
 - Whether or not it should be enabled on spawn. If disabled, the virtual Arduino will not be able to transmit or receive any data until turned on through a virtual input.
 - Whether or not the virtual Arduino should convert all strings sent by the physical Arduino to numbers. This is useful for communicating with Wiremod entities that only accept numbers for certain inputs.
 - The name of the serial port the physical Arduino is connected to. This is required to make the virtual Arduino function properly.
 - The model of the virtual Arduino. Model options are the same as the Wiremod CPU.

 Once you spawn it in, you can get to work connecting things as inputs, outputs, or both depending entirely on what you want to do, and then writing code for your physical Arduino to react to those inputs/outputs.

## Contributing
 Contributions are welcome! Please read through the [guidelines](https://lambdagaming.github.io/guides/contributing) before submitting an issue or pull request.
