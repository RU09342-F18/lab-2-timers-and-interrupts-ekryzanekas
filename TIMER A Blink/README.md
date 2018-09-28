These programs have the same functionality as a LED blinking from last lab, but instead of using delays, the LED blinks from the
built in timers. The LED is set as an output, and interrupts are enables on the timer. When the Capture/compare reaches the value
set to the timer, it starts an interrupt. The interrupt vector then toggles the LED and then resets flags, to allow a cycle. 