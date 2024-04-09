#include "character_lcd_8bit.hpp"

CharacterLCD_8Bit::CharacterLCD_8Bit(uint8_t columns, uint8_t rows, uint rs, uint en, uint d0, uint d1, uint d2, uint d3, uint d4, uint d5, uint d6, uint d7) : CharacterLCD_GPIO(columns, rows, rs, en) {
    this->d[0] = new DigitalInOut_GPIO(d0);
    this->d[1] = new DigitalInOut_GPIO(d1);
    this->d[2] = new DigitalInOut_GPIO(d2);
    this->d[3] = new DigitalInOut_GPIO(d3);
    this->d[4] = new DigitalInOut_GPIO(d4);
    this->d[5] = new DigitalInOut_GPIO(d5);
    this->d[6] = new DigitalInOut_GPIO(d6);
    this->d[7] = new DigitalInOut_GPIO(d7);
    for (uint8_t i = 0; i < 8; i++) {
        this->d[i]->set_dir(true);
    }

    this->display_function |= LCD_8BITMODE;
    this->init();
};

CharacterLCD_8Bit::CharacterLCD_8Bit(uint8_t columns, uint8_t rows, DigitalInOut *rs, DigitalInOut *en, DigitalInOut *d0, DigitalInOut *d1, DigitalInOut *d2, DigitalInOut *d3, DigitalInOut *d4, DigitalInOut *d5, DigitalInOut *d6, DigitalInOut *d7) : CharacterLCD_GPIO(columns, rows, rs, en) {
    this->d[0] = d0;
    this->d[1] = d1;
    this->d[2] = d2;
    this->d[3] = d3;
    this->d[4] = d4;
    this->d[5] = d5;
    this->d[6] = d6;
    this->d[7] = d7;
    for (uint8_t i = 0; i < 8; i++) {
        this->d[i]->set_dir(true);
    }

    this->display_function |= LCD_8BITMODE;
    this->init();
};

CharacterLCD_8Bit::~CharacterLCD_8Bit() {
    for (uint8_t i = 0; i < 8; i++) {
        delete this->d[i];
    }
};

void CharacterLCD_8Bit::put(uint8_t value) {
    this->put(value, false);
};

void CharacterLCD_8Bit::put(uint8_t value, bool char_mode) {
    uint8_t i;

    // 1ms delay to prevent writing too quickly
    sleep_ms(1);

    // Set character/data bit
    this->rs->put(char_mode);

    // Write byte
    for (i = 0; i < 8; i++) {
        this->d[i]->put((value >> i) & 0x01);
    }
    // NOTE: Could be sped up with data prep and single mask write
    this->pulse_enable();

};
