#include <button.h>
Button::Button()
{
    state = 0;
    PORT = 0;
    PIN = 0;
}

Button::~Button()
{
}

Button::Button(volatile uint8_t *PORT, uint8_t PIN)
{
    this->PORT = PORT;
    this->PIN = PIN;
}

uint8_t Button::update()
{
    volatile uint16_t temp = *PORT;
    state = (state << 1) | (!((temp & (1 << PIN)) >> PIN));
    // state &= 0b11111111;
    return state;
}
uint8_t Button::read()
{
    switch (state)
    {
    case 0b01111111:
        return B_TRIG;
        break;
    case 0b11111111:
        return B_HOLD;
        break;
    case 0b11111110:
        return B_REL;
        break;
    default:
        return B_OFF;
        break;
    }
}