#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//IN/OUT info
	P1DIR |= BIT0; //makes LED output
	P1DIR &= ~BIT1; //sets button as input
	P1REN |= BIT1; //enables resistor
	P1OUT |= BIT1; //pull up resistor

	//INTERRUPT INFO
	P1IE |= BIT1;  //makes button interrupt
	P1IES |= BIT1; // sets neg edge to set

	 _BIS_SR(LPM0_bits + GIE);

}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    P1OUT ^= BIT0; // Toggle P1.0
    P1IFG &= ~BIT1; // clear flag for button interrupt
}
