#pragma once
#include <stdint.h>
#define B_TRIG 1
#define B_HOLD 2
#define B_REL 3
#define B_OFF 0
class Button
{
public:
    Button();
    Button(volatile uint8_t *PORT, uint8_t PIN);
    ~Button();

    uint8_t update();
    uint8_t read(uint8_t do_read = 0);

private:
    uint16_t state;
    volatile uint8_t *PORT;
    uint16_t PIN;
};
