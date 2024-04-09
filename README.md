# pico-character-lcd
Character LCD library for the Raspberry Pi Pico C/C++ SDK.

## Installation
Make sure that [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk) is installed correctly before following the instructions below.

### Example Compilation
Clone the library using `git clone https://github.com/dcooperdalrymple/pico-character-lcd` into a suitable location. Run the following commands to build the library example and ensure that your machine is capable of building this software.

````
cd pico-character-lcd/example
mkdir build && cd build
cmake ..
make
````

### Install Extension into Your Project
In order to add this library as an extension of your project, insert it as a submodule using `git submodule add https://github.com/dcooperdalrymple/pico-character-lcd.git` into the desired location. In the `CMakeLists.txt` file, insert `add_subdirectory(./{PATH_TO_SUBMODULE}/pico-character-lcd)` below your source files (ie: `add_executable(...)`). Then add `pico_character_lcd` to your list of _target_link_libraries_ such as `target_link_libraries(... pico_character_lcd ...)`.

## Usage
See `./example/pico-character-lcd-example.cpp` for implementation.

## Citations

* [raspberrypi/pico-examples](https://github.com/raspberrypi/pico-examples/tree/main/i2c/lcd_1602_i2c/)
* [adafruit/Adafruit_CircuitPython_CharLCD](https://github.com/adafruit/Adafruit_CircuitPython_CharLCD/)
