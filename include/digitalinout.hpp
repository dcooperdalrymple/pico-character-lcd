#pragma once
#include "pico/stdlib.h"

class DigitalInOut {

public:
    DigitalInOut() { };
    virtual ~DigitalInOut() { };

    virtual void set_dir(bool out) { };
    virtual bool get_dir() { };

    virtual void put(bool value) { };
    virtual bool get() { };

};

class DigitalInOut_GPIO : public DigitalInOut {

public:
    DigitalInOut_GPIO(uint pin);
    ~DigitalInOut_GPIO();

    void set_dir(bool out);
    bool get_dir();

    void put(bool value);
    bool get();

private:
    uint pin;

};
