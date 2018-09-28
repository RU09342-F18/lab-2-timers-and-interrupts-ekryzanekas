The functionality of this program is the same as Button Blink from the previous lab. Instead of polling to check if the button
is pressed and using delays, interrupts were enabled on the button. When the button was pressed, the interrupt vector directed
the processor to toggle the LED then reset the interrupt flag. 