#include "mcp23008.hpp"
#include <cstdlib>

MCP23008::MCP23008(i2c_inst_t *i2c, uint sda, uint scl, uint8_t address, bool reset) {
    this->init(i2c, sda, scl, address);
    if (reset) this->reset();
};
MCP23008::MCP23008(i2c_inst_t *i2c, uint sda, uint scl, uint8_t address) {
    this->init(i2c, sda, scl, address);
    this->reset();
};
MCP23008::MCP23008(i2c_inst_t *i2c, uint sda, uint scl) {
    this->init(i2c, sda, scl, MCP23008_ADDRESS);
    this->reset();
};
MCP23008::MCP23008() {
    this->init(i2c_default, PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, MCP23008_ADDRESS);
    this->reset();
};

void MCP23008::init(i2c_inst_t *i2c, uint sda, uint scl, uint8_t address) {
    this->i2c = i2c;
    this->sda = sda;
    this->scl = scl;
    this->address = address;

    this->iodir = 0xFF;
    this->gppu = 0x00;

    i2c_init(this->i2c, 100000);
    gpio_set_function(this->sda, GPIO_FUNC_I2C);
    gpio_set_function(this->scl, GPIO_FUNC_I2C);
    gpio_pull_up(this->sda);
    gpio_pull_up(this->scl);
};

MCP23008::~MCP23008() {
    i2c_deinit(this->i2c);
    gpio_disable_pulls(this->sda);
    gpio_disable_pulls(this->scl);
    gpio_deinit(this->sda);
    gpio_deinit(this->scl);
};

DigitalInOut_MCP *MCP23008::get_pin(uint8_t pin) {
    return new DigitalInOut_MCP(this, pin);
}

void MCP23008::reset() {
    this->iodir = 0xFF;
    this->gppu = 0x00;
    this->write(MCP23008_IPOL, 0x00);
};

uint8_t MCP23008::get_gpio() {
    return this->read(MCP23008_GPIO);
};

void MCP23008::set_gpio(uint8_t value) {
    this->write(MCP23008_GPIO, value);
};

uint8_t MCP23008::get_iodir() {
    return this->read(MCP23008_IODIR);
};

void MCP23008::set_iodir(uint8_t value) {
    this->write(MCP23008_IODIR, value);
};

uint8_t MCP23008::get_gppu() {
    return this->read(MCP23008_GPPU);
};

void MCP23008::set_gppu(uint8_t value) {
    this->write(MCP23008_GPPU, value);
};

uint8_t MCP23008::read(uint8_t address) {
    uint8_t value;
    i2c_write_blocking(this->i2c, this->address, &address, 1, true);
    i2c_read_blocking(this->i2c, this->address, &value, 1, false);
    return value;
};

void MCP23008::write(uint8_t address, uint8_t value) {
    uint8_t *buffer;
    buffer = (uint8_t *)malloc(2 * sizeof(uint8_t));
    buffer[0] = address;
    buffer[1] = value;
    i2c_write_blocking(this->i2c, this->address, buffer, 2, true);
    delete buffer;
};

DigitalInOut_MCP::DigitalInOut_MCP(MCP23008 *device, uint8_t pin) : DigitalInOut() {
    this->device = device;
    this->pin = pin;
};

void DigitalInOut_MCP::set_dir(bool out) {
    if (out) {
        this->device->set_iodir(this->device->get_iodir() | (1 << this->pin));
    } else {
        this->device->set_iodir(this->device->get_iodir() & ~(1 << this->pin));
    }
};

bool DigitalInOut_MCP::get_dir() {
    return this->device->get_iodir() & (1 << this->pin);
};

void DigitalInOut_MCP::put(bool value) {
    if (value) {
        this->device->set_gpio(this->device->get_gpio() | (1 << this->pin));
    } else {
        this->device->set_gpio(this->device->get_gpio() & ~(1 << this->pin));
    }
};

bool DigitalInOut_MCP::get() {
    return this->device->get_gpio() & (1 << this->pin);
};
