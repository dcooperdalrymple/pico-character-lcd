cmake_minimum_required(VERSION 3.13)

set(NAME pico_character_lcd)
set(URL "https://github.com/dcooperdalrymple/pico-character-lcd")

add_library(${NAME} INTERFACE)

target_sources(${NAME} INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/digitalinout.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/mcp23008.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/character_lcd.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/character_lcd_gpio.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/character_lcd_4bit.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/character_lcd_8bit.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/character_lcd_i2c.cpp
)

target_include_directories(${NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

# Pull in pico libraries that we need
target_link_libraries(${NAME} INTERFACE pico_stdlib pico_float hardware_gpio hardware_i2c)
