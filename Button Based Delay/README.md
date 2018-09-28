This program sets the frequency of the LED blinking to the time that the button is pressed. Initially, the timer is in up mode
to trigger the LED toggle, the same way as in the previous part of the lab. There are interrupts enable on the pos edge of the 
button, so an interrupt will be enabled when the button is pressed. The interrupt vector tells the timer to count in 
continuous mode when the button is pressed, and then set the interrupt flag on the neg edge of the button, so when the button 
is let go, the value that it counted to will be copied and put into the timer register. It will also set the timer to count back
to up mode and clear the flag after the button is let go. 