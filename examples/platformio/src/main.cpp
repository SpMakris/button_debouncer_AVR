#include <Arduino.h>
#include <button.h>
Button test(&PINB, 0x4);
void setup()
{
  // put your setup code here, to run once:
  DDRB = 0xFF;
  DDRB &= (0b11111110 << PINB4);
  PORTB = 0;

}

void loop()
{
  if (test.read(1) == B_TRIG)
  {
    PORTB ^= (1 << 5);
  }
}