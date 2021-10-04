#pragma once
// #include <Arduino.h>
#include <stdint.h>
#define B_TRIG 1
#define B_HOLD 2
#define B_REL 3
#define B_OFF 0
class Button
{
public:
	Button()
	{
		state = 0;
		PORT = 0;
		PIN = 0;
	}

	Button(volatile uint8_t *PORT, uint8_t PIN)
	{
		this->PORT = PORT;
		this->PIN = PIN;
	}
	~Button()
	{
	}

	//read the button state
	uint8_t update()
	{
		volatile uint8_t temp = *PORT;
		state = (state << 1) | (!((temp & (1 << PIN)) >> PIN));
		// state &= 0b11111111;
		return state;
	}

	//read the button state
	//give argument of 1 to also perform a button update
	uint8_t read(uint8_t do_read = 0)
	{
		if (do_read == 1)
		{
			update();
		}
		switch (state)
		{
		case (0xFF >> 1):
			return B_TRIG;
			break;
		case 0xFF:
			return B_HOLD;
			break;
		case (0xFF - 1):
			return B_REL;
			break;
		default:
			return B_OFF;
			break;
		}
	}

private:
	uint8_t state;
	volatile uint8_t *PORT;
	uint8_t PIN;
};
