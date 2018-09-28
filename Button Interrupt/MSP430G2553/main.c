#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR &= ~BIT3; //makes button the input
	P1DIR |= BIT0; // sets LED to output
	P1REN |= BIT3; //enables resistor for button
	P1OUT |= BIT3; // pulldown resistor. Input will be 0 when button is not pressed
	P1IE |= BIT3;
	P1IES &= ~BIT3; // interrupt triggers on rising edge (button pressed)
	P1IFG &= ~BIT3; //clears flag (i dont know what this means but I know it is necessary)

	_BIS_SR(LPM0_bits + GIE); // global interupt enable

	return 0;

}

#pragma vector = PORT1_VECTOR;
__interrupt void Port_1(void)
{
    P1OUT ^= BIT0;
    P1IFG &= ~BIT3;
}
