#include "character_lcd.hpp"
#include <cstdlib>
#include "pico/float.h"

CharacterLCD::CharacterLCD(uint8_t columns, uint8_t rows) {
    // LCD character resolution
    if (columns > LCD_MAXCOLS || !columns) columns = LCD_MAXCOLS;
    if (rows > LCD_MAXROWS || !rows) rows = LCD_MAXROWS;
    this->columns = columns;
    this->rows = rows;

    // Cursor position
    this->row = 0;
    this->column = 0;

    // Initialize display registers
    this->display_control = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    this->display_function = LCD_4BITMODE | LCD_1LINE | LCD_2LINE | LCD_5x8DOTS;
    this->display_mode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;

    // Setup buffer
    this->input_buffer = (char *)malloc(this->rows * this->columns * sizeof(char));
    this->output_buffer = (char *)malloc(this->rows * this->columns * sizeof(char));
    this->reset_buffer();
};

CharacterLCD::~CharacterLCD() {
    free(this->input_buffer);
    free(this->output_buffer);
};

void CharacterLCD::init() {
    // Initialize display
    this->put(0x33);
    this->put(0x32);

    this->put(LCD_DISPLAYCONTROL | this->display_control);
    this->put(LCD_FUNCTIONSET | this->display_function);
    this->put(LCD_ENTRYMODESET | this->display_mode);

    this->clear();
};

void CharacterLCD::home() {
    this->put(LCD_RETURNHOME);
    sleep_ms(3);
};

void CharacterLCD::clear() {
    this->put(LCD_CLEARDISPLAY);
    sleep_ms(3);
    this->reset_buffer();
};
void CharacterLCD::reset_buffer(bool reset_out) {
    for (uint8_t i = 0; i < this->rows * this->columns; i++) {
        this->input_buffer[i] = '\0';
        if (reset_out) this->output_buffer[i] = ' ';
    }
    this->needs_update = false;
};
void CharacterLCD::reset_buffer() {
    this->reset_buffer(true);
};

bool CharacterLCD::cursor_enabled() {
    return this->display_control & LCD_CURSORON;
};

void CharacterLCD::cursor(bool enable) {
    if (enable) {
        this->display_control |= LCD_CURSORON;
    } else {
        this->display_control &= ~LCD_CURSORON;
    }
    this->put(LCD_DISPLAYCONTROL | this->display_control);
};

void CharacterLCD::cursor_position(uint8_t column, uint8_t row, bool update_pos) {
    if (row >= this->rows) row = this->rows - 1;
    if (column >= this->columns) column = this->columns - 1;
    this->put(LCD_SETDDRAMADDR | (column + LCD_ROW_OFFSETS[row]));
    if (update_pos) {
        this->row = row;
        this->column = column;
    }
};
void CharacterLCD::cursor_position(uint8_t column, uint8_t row) {
    this->cursor_position(column, row, true);
};

bool CharacterLCD::blink_enabled() {
    return this->display_control & LCD_BLINKON;
};

void CharacterLCD::blink(bool enable) {
    if (enable) {
        this->display_control |= LCD_BLINKON;
    } else {
        this->display_control &= ~LCD_BLINKON;
    }
    this->put(LCD_DISPLAYCONTROL | this->display_control);
};

bool CharacterLCD::display_enabled() {
    return this->display_control & LCD_DISPLAYON;
};

void CharacterLCD::display(bool enable) {
    if (enable) {
        this->display_control |= LCD_DISPLAYON;
    } else {
        this->display_control &= ~LCD_DISPLAYON;
    }
    this->put(LCD_DISPLAYCONTROL | this->display_control);
};

void CharacterLCD::write(const char * data, uint8_t col, uint8_t row, uint8_t len, bool right_aligned) {
    uint8_t i, j, pad = 0;

    col = MIN(col, this->columns-1);
    row = MIN(row, this->rows-1);
    if (!len) len = 16;
    len = CLAMP(len, 1, this->columns-col);

    if (right_aligned) {
        i = 0;
        while (data[i] != '\0') { i++; }
        if (i < len) pad = len - i;
    }

    for (i = 0, j = 0; i < len; i++) {
        this->input_buffer[col + i + row * this->rows] = ((i >= pad && data[j] != '\0') ? data[j++] : ' ');
    }
    this->needs_update = true;

    // TODO: Handle newline?
};
void CharacterLCD::write(const char * data, uint8_t col, uint8_t row, uint8_t len) {
    this->write(data, col, row, len, false);
};
void CharacterLCD::write(const char * data, uint8_t col, uint8_t row) {
    this->write(data, col, row, 0);
};
void CharacterLCD::write(const char * data) {
    this->write(data, 0, 0);
};

void CharacterLCD::update(bool reset_cursor) {
    uint8_t i, end = 255, start = 255, len;

    // Exit early if no buffer updates recorded
    if (!this->needs_update) return;

    // Locate the end of input buffer data
    for (i = this->columns * this->rows - 1; i != 255; i--) {
        if (this->input_buffer[i] == '\0' || this->input_buffer[i] == this->output_buffer[i]) continue;
        end = i;
        break;
    }
    if (end == 255) return; // No changes found

    // Locate the start of input buffer data
    for (i = 0; i < this->columns * this->rows; i++) {
        if (this->input_buffer[i] == '\0' || this->input_buffer[i] == this->output_buffer[i]) continue;
        start = i;
    }
    len = start - end + 1;

    // Set cursor position
    this->cursor_position(start % this->columns, start / this->columns, !reset_cursor);

    // Copy input buffer into output buffer and send data
    for (i = start; i <= end; i++) {
        if (this->input_buffer[i] == '\0') continue;
        this->output_buffer[i] = this->input_buffer[i];
        this->put(this->output_buffer[i]);
    }

    // Return cursor position to original
    if (reset_cursor) this->cursor_position(this->column, this->row);

    // Reset input buffer
    this->reset_buffer(false);
};
void CharacterLCD::update() {
    this->update(false);
};

void CharacterLCD::move_left() {
    this->put(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
    // TODO: Update buffer?
};

void CharacterLCD::move_right() {
    this->put(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
    // TODO: Update buffer?
};

void CharacterLCD::create_char(uint8_t location, uint8_t * pattern) {
    location &= 0x07;
    this->put(LCD_SETCGRAMADDR | (location << 3));
    for (int i = 0; i < LCD_CHARSIZE; i++) {
        this->put(pattern[i], true);
    }
};

void CharacterLCD::enable_vertical_graph() {
    uint8_t i, j;
    uint8_t * data = (uint8_t *)malloc(LCD_CHARSIZE * sizeof(uint8_t));
    for (i = 1; i < 8; i++) {
        for (j = 0; j < LCD_CHARSIZE - i; j++) {
            data[j] = 0x00;
        }
        for (j = LCD_CHARSIZE - i; j < LCD_CHARSIZE; j++) {
            data[j] = 0x1f;
        }
        this->create_char(i-1, data);
    }
    free(data);
};

void CharacterLCD::enable_horizontal_graph() {
    uint8_t i, j, val;
    uint8_t * data = (uint8_t *)malloc(LCD_CHARSIZE * sizeof(uint8_t));
    // Left to right
    for (i = 1; i < 5; i++) {
        val = 0x00;
        for (j = 0; j < i; j++) {
            val |= 1 << (4-j);
        }
        for (j = 0; j < LCD_CHARSIZE; j++) {
            data[j] = val;
        }
        this->create_char(i-1, data);
    }
    // Right to left
    for (i = 1; i < 5; i++) {
        val = 0x00;
        for (j = 0; j < i; j++) {
            val |= 1 << j;
        }
        for (j = 0; j < LCD_CHARSIZE; j++) {
            data[j] = val;
        }
        this->create_char(i+3, data);
    }
};

void CharacterLCD::write_vertical_graph(uint8_t value, uint8_t col, uint8_t row, uint8_t height) {
    this->write_graph(value, col, row, height, true, false);
};
void CharacterLCD::write_vertical_graph(uint8_t value, uint8_t col, uint8_t row) {
    this->write_vertical_graph(value, col, row, 1);
};

void CharacterLCD::write_horizontal_graph(uint8_t value, uint8_t col, uint8_t row, uint8_t width, bool centered) {
    this->write_graph(value, col, row, width, false, centered);
};
void CharacterLCD::write_horizontal_graph(uint8_t value, uint8_t col, uint8_t row, uint8_t width) {
    this->write_horizontal_graph(value, col, row, width, false);
};
void CharacterLCD::write_horizontal_graph(uint8_t value, uint8_t col, uint8_t row) {
    this->write_horizontal_graph(value, col, row, 1);
};

void CharacterLCD::write_graph(float value, uint8_t col, uint8_t row, uint8_t len, bool vertical, bool centered) {
    // TODO: Convert this to only use integers (0<value<255)

    value = CLAMP(value, 0.0f, 1.0f);
    col = MIN(col, this->columns);
    row = MIN(row, this->rows);
    len = CLAMP(len, 1, vertical ? this->rows - row : this->columns - col);

    float segment = 1.0f / len;
    float bar = segment / (vertical ? 9.0f : 6.0f);

    char * data = (char *)malloc(len * sizeof(char));
    uint8_t start = 0, i;

    if (!vertical && centered) {
        start = len >> 1; // /2
        for (i = 0; i < start; i++) {
            if (value <= segment * i + bar) {
                data[i] = 0xff;
            } else if (value >= segment * (i+1) - bar) {
                data[i] = 0xfe;
            } else {
                data[i] = 0x07 - (uint8_t)(floor((value - (segment * i + bar)) / bar));
            }
        }
    }

    for (i = start; i < len; i++) {
        if (value >= segment * (i + 1) - bar) {
            data[i] = 0xff;
        } else if (value <= segment * i + bar) {
            data[i] = 0xfe;
        } else {
            data[i] = 0x00 + (uint8_t)(floor((value - (segment * i + bar)) / bar));
        }
    }

    // Write graph data to input buffer
    for (i = 0; i < len; i++) {
        // Convert \0 to spaces
        if (data[i] == '\0') data[i] = ' ';

        if (vertical) {
            this->input_buffer[(row + len-i-1) * this->columns + col] = data[i];
        } else {
            this->input_buffer[row * this->columns + col + i] = data[i];
        }
    }
    this->needs_update = true;

};
