# GMSerial
 Formerly known as Arduino Gmod Interface. GMSerial is an experimental binary module for Garry's Mod that allows the game to communicate with serial devices (such as Arduino), and vice versa. This repo contains the base addon, the binary module, and a Wiremod tool. The module is based on [serial_cpp.](https://github.com/gbionics/serial_cpp) It works on Windows and Linux on the 64-bit version of the game.

# Installing
 1. Download this repo as a zip
 2. Extract it to `[Steam folder]/steamapps/common/GarrysMod/garrysmod/addons/[addon name]`
 3. Download the binary module from [here.](https://github.com/LambdaGaming/GMSerial/releases)
 4. Move it to `[Steam folder]/steamapps/common/GarrysMod/garrysmod/lua/bin`. You might have to create the bin folder since it doesn't exist by default.
 5. Plug in a serial device, launch the game, and you should now be able to use the API and Wiremod tool! If you need help with the API, check out the [documentation](dev.md) and take a look at the [examples.](examples)
 
 >[!NOTE]
 > If you're on Linux, you might get a permission denied error when trying to establish a connection. You can fix this by entering the following command: `sudo usermod -a -G $(stat -c "%G" /dev/ttyS1) $USER`. Replace `/dev/ttyS1` with the port name of your device. This will add your user account to the groups your device belongs to so you can access it without root privileges.

# Using the Wiremod Tool
 Ensure you have the base and [Wiremod](https://steamcommunity.com/sharedfiles/filedetails/?id=160250458) downloaded, and a serial device plugged into your PC. Obviously, the device must be programmed to send or receive data.

 The Wiremod tool can be found in the "Chips, Gates" category. Once you have it selected, you can change various settings that include:
 - Whether or not it should be enabled on spawn. If disabled, the virtual device will not be able to transmit or receive any data until turned on through a virtual input.
 - Whether or not the virtual device should convert all strings received from the physical device to numbers. This is useful for communicating with Wiremod entities that only accept numbers for certain inputs.
 - The name of the serial port the physical device is connected to. This is required to establish a connection.
 - The baudrate of the physical device. This is also required.
 - The timeout between read/writes.
 - The model of the virtual device. Model options are the same as the Wiremod CPU.

 Once you spawn it in, you can get to work connecting things as inputs, outputs, or both depending entirely on what you want to do, and then programming your physical device to react to those signals.

# Building
1. Install Git and CMake.
2. Clone this repo with Git.
3. Run `build_linux.sh` if you're on Linux and `build_windows.bat` if you're on Windows. The dll files will be in the src folder.

# Contributing
 Contributions are welcome! Please read through the [guidelines](https://lambdagaming.github.io/guides/contributing) before submitting an issue or pull request.
