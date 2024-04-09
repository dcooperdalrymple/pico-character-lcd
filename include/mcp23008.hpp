#pragma once
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "digitalinout.hpp"

const uint8_t MCP23008_ADDRESS = 0x20;
const uint8_t MCP23008_IODIR   = 0x00;
const uint8_t MCP23008_IPOL    = 0x01;
const uint8_t MCP23008_GPINTEN = 0x02;
const uint8_t MCP23008_DEFVAL  = 0x03;
const uint8_t MCP23008_INTCON  = 0x04;
const uint8_t MCP23008_IOCON   = 0x05;
const uint8_t MCP23008_GPPU    = 0x06;
const uint8_t MCP23008_INTF    = 0x07;
const uint8_t MCP23008_INTCAP  = 0x08;
const uint8_t MCP23008_GPIO    = 0x09;

class DigitalInOut_MCP;

class MCP23008 {

public:
    MCP23008(i2c_inst_t *i2c, uint sda, uint scl, uint8_t address, bool reset);
    MCP23008(i2c_inst_t *i2c, uint sda, uint scl, uint8_t address);
    MCP23008(i2c_inst_t *i2c, uint sda, uint scl);
    MCP23008();
    ~MCP23008();

    void reset();

    DigitalInOut_MCP *get_pin(uint8_t pin);

    uint8_t get_gpio();
    void set_gpio(uint8_t value);

    uint8_t get_iodir();
    void set_iodir(uint8_t value);

    uint8_t get_gppu();
    void set_gppu(uint8_t value);

private:
    i2c_inst_t *i2c;
    uint sda, scl;
    uint8_t address;
    uint8_t iodir, gppu;

    void init(i2c_inst_t *i2c, uint sda, uint scl, uint8_t address);

    void write(uint8_t address, uint8_t value);
    uint8_t read(uint8_t address);

};

class DigitalInOut_MCP : public DigitalInOut {

public:
    DigitalInOut_MCP(MCP23008 *device, uint8_t pin);
    ~DigitalInOut_MCP() { };

    void set_dir(bool out);
    bool get_dir();

    void put(bool value);
    bool get();

private:
    MCP23008 *device;
    uint8_t pin;

};
