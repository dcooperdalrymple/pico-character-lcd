#include "character_lcd_4bit.hpp"

CharacterLCD_4Bit::CharacterLCD_4Bit(uint8_t columns, uint8_t rows, uint rs, uint en, uint d4, uint d5, uint d6, uint d7) : CharacterLCD_GPIO(columns, rows, rs, en) {
    this->d[0] = new DigitalInOut_GPIO(d4);
    this->d[1] = new DigitalInOut_GPIO(d5);
    this->d[2] = new DigitalInOut_GPIO(d6);
    this->d[3] = new DigitalInOut_GPIO(d7);
    for (uint8_t i = 0; i < 4; i++) {
        this->d[i]->set_dir(true);
    }
};

CharacterLCD_4Bit::CharacterLCD_4Bit(uint8_t columns, uint8_t rows, DigitalInOut *rs, DigitalInOut *en, DigitalInOut *d4, DigitalInOut *d5, DigitalInOut *d6, DigitalInOut *d7) : CharacterLCD_GPIO(columns, rows, rs, en) {
    this->d[0] = d4;
    this->d[1] = d5;
    this->d[2] = d6;
    this->d[3] = d7;
    for (uint8_t i = 0; i < 4; i++) {
        this->d[i]->set_dir(true);
    }
};

CharacterLCD_4Bit::~CharacterLCD_4Bit() {
    for (uint8_t i = 0; i < 4; i++) {
        delete this->d[i];
    }
};

void CharacterLCD_4Bit::put(uint8_t value) {
    this->put(value, false);
};

void CharacterLCD_4Bit::put(uint8_t value, bool char_mode) {
    uint8_t i;

    // 1ms delay to prevent writing too quickly
    sleep_ms(1);

    // Set character/data bit
    this->rs->put(char_mode);

    // Write upper 4 bits
    for (i = 0; i < 4; i++) {
        this->d[i]->put((value >> (4 + i)) & 0x01);
    }
    this->pulse_enable();

    // Write lower 4 bits
    for (i = 0; i < 4; i++) {
        this->d[i]->put((value >> i) & 0x01);
    }
    this->pulse_enable();
};
