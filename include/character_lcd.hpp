#pragma once
#include "pico/stdlib.h"

#ifndef CLAMP
#define CLAMP(a, b, c) (MIN(MAX(a, b), c))
#endif

// Commands
const uint8_t LCD_CLEARDISPLAY   = 0x01;
const uint8_t LCD_RETURNHOME     = 0x02;
const uint8_t LCD_ENTRYMODESET   = 0x04;
const uint8_t LCD_DISPLAYCONTROL = 0x08;
const uint8_t LCD_CURSORSHIFT    = 0x10;
const uint8_t LCD_FUNCTIONSET    = 0x20;
const uint8_t LCD_SETCGRAMADDR   = 0x40;
const uint8_t LCD_SETDDRAMADDR   = 0x80;

// Entry flags
const uint8_t LCD_ENTRYSHIFTDECREMENT = 0x00;
const uint8_t LCD_ENTRYSHIFTINCREMENT = 0x01;
const uint8_t LCD_ENTRYLEFT           = 0x02;

// Control flags
const uint8_t LCD_BLINKOFF  = 0x00;
const uint8_t LCD_BLINKON   = 0x01;
const uint8_t LCD_CURSOROFF = 0x00;
const uint8_t LCD_CURSORON  = 0x02;
const uint8_t LCD_DISPLAYON = 0x04;

// Move flags
const uint8_t LCD_MOVELEFT    = 0x00;
const uint8_t LCD_MOVERIGHT   = 0x04;
const uint8_t LCD_DISPLAYMOVE = 0x08;

// Function set flags
const uint8_t LCD_5x8DOTS  = 0x00;
const uint8_t LCD_5x10DOTS = 0x04;
const uint8_t LCD_1LINE    = 0x00;
const uint8_t LCD_2LINE    = 0x08;
const uint8_t LCD_4BITMODE = 0x00;
const uint8_t LCD_8BITMODE = 0x10;

// Miscellaneous control flags
const uint8_t LCD_ENABLE_BIT = 0x04;
const uint8_t LCD_BACKLIGHT  = 0x08;

// Offset for up to 4 rows
const uint8_t LCD_ROW_OFFSETS[] = { 0x00, 0x40, 0x14, 0x54};

// By default, the LCD display driver assumes bus address 0x27
static uint8_t LCD_ADDR = 0x27;

#define LCD_MAXCOLS   16
#define LCD_MAXROWS   4
#define LCD_CHARSIZE  8

class CharacterLCD {

public:
    CharacterLCD(uint8_t columns, uint8_t rows);
    ~CharacterLCD();

    void home();
    void clear();

    bool cursor_enabled();
    void cursor(bool enable);
    void cursor_position(uint8_t column, uint8_t row, bool update_pos);
    void cursor_position(uint8_t column, uint8_t row);

    bool blink_enabled();
    void blink(bool enable);
    
    bool display_enabled();
    void display(bool enable);

    void write(const char * data, uint8_t col, uint8_t row, uint8_t len, bool right_aligned);
    void write(const char * data, uint8_t col, uint8_t row, uint8_t len);
    void write(const char * data, uint8_t col, uint8_t row);
    void write(const char * data);

    void update(bool reset_cursor);
    void update();

    void move_left();
    void move_right();

    void create_char(uint8_t location, uint8_t * pattern);

    // Graph helpers
    void enable_vertical_graph();
    void enable_horizontal_graph();

    void write_vertical_graph(uint8_t value, uint8_t col, uint8_t row, uint8_t height);
    void write_vertical_graph(uint8_t value, uint8_t col, uint8_t row);
    
    void write_horizontal_graph(uint8_t value, uint8_t col, uint8_t row, uint8_t width, bool centered);
    void write_horizontal_graph(uint8_t value, uint8_t col, uint8_t row, uint8_t width);
    void write_horizontal_graph(uint8_t value, uint8_t col, uint8_t row);

protected:
    // Must be called within constructor of subclass which implements `put`
    void init();

    virtual void put(uint8_t value) { };
    virtual void put(uint8_t value, bool char_mode) { };

private:
    // Parameters
    uint8_t columns, rows;

    // Control flags
    uint8_t display_control, display_function, display_mode;

    // Cursor position
    uint8_t column, row;

    // Buffer
    char * input_buffer;
    char * output_buffer;
    bool needs_update;
    void reset_buffer(bool reset_out);
    void reset_buffer();

    // Graph helpers
    void write_graph(float value, uint8_t col, uint8_t row, uint8_t len, bool vertical, bool centered);

};
