# AVR button class
Mechanical switches are known for exhibiting a behavior refered to as "bouncing". When a button is pressed, the contacts make or break the circuit, however this doesn't happen smoothly. Typically, a contact will oscillate between the on and off states for a few milliseconds; any system reading the button in this interval will produce erroneous readings.
There are various techniques, but in software and hardware that deal with this. The particular method used in this class is optimised for the AVR core, using 8bit variables and
a small number of bitwise commands, making it ideal for using within an ISR. Furthermore, it doesn't use any timers and thus will not interfere with the rest of your application.

#Working Concept
When reading the state of the button, there is a period of oscillation before the value settles to its proper position. We assume that the final state is reached when 8 concecutive reads are identical, ie read 8 concecutive 0's or 1's. We can identify 4 different states that are of use to us:
1. Trigger
The button is just pressed. This state is guaranteed to appear first when the button is successfully pressed and only appear once during a press cycle.

2. Hold
The button has been pressed and is now held down. This state appears after a Trigger and will persist as long as the button is held down.

3. Release
The button has just been released, after being pressed down (Hold). This state is guaranteed to appear after a Hold state, and is only activated once.

4. Off
The button is not pressed.

In order to achieve the above, we read the values read from the button pin and shift them into an 8bit register (uint8_t variable). Depending on the value of this register the state of the button can be deduced:
1. 0b01111111 -> Trigger . 7 concecutive 1's have been read, the next 1 will place the button in the hold state. 
2. 0b11111111 -> Hold . 8 concecutive 1's have been read, therefore the button is being held down
3. 0b10000000 -> Release. 7 Concecutive 0's have been read, after a Hold condition, thefore the button is being released
4. 0b00000000 -> Off. No 1's have been read, thus the button is Off.

#Basic Usage





