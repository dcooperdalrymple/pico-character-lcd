#include "digitalinout.hpp"

DigitalInOut_GPIO::DigitalInOut_GPIO(uint pin) : DigitalInOut() {
    this->pin = pin;
    gpio_init(this->pin);
};

DigitalInOut_GPIO::~DigitalInOut_GPIO() {
    gpio_deinit(this->pin);
};

void DigitalInOut_GPIO::set_dir(bool out) {
    gpio_set_dir(this->pin, out);
};

bool DigitalInOut_GPIO::get_dir() {
    return gpio_get_dir(this->pin);
}

void DigitalInOut_GPIO::put(bool value) {
    gpio_put(this->pin, value);
};

bool DigitalInOut_GPIO::get() {
    return gpio_get(this->pin);
};
