#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5; //unlock I/O pins

	//IN/OUT INFO
	P1DIR |= BIT0; //LED output
	P1DIR &= ~BIT1; //button input
	P1REN |= BIT1; //resistor enable for button
	P1OUT |= BIT1; //enables pull down resistor


	//INTERRUPT INFO
	P1IE |= BIT1; // sets interrupt for button
	P1IES |= BIT1; // pos edge trigger for button
	TB0CTL=TBSSEL_1 + MC_1 + ID_3; // clock 8 divider and up counter
	TB0CCR0 = 500; //sets CCR counting
	TB0CCTL0 |= CCIE; //interrupt enable for TB0
	_BIS_SR(LPM0_bits + GIE); //global interrupt enable
}
	

#pragma vector=TIMER0_B0_VECTOR
__interrupt void TIMER0_B0(void) {

    P1OUT ^= BIT0;//toggle LED
}

#pragma vector = PORT1_VECTOR;
    __interrupt void Port_1(void)
    {
       if (P1IES & BIT1) //if button is pressed
       {
           P1IES &= ~BIT1;//set to neg edge
           TBCTL = TBCLR;//clear the time
           TB0CTL=TBSSEL_1 + MC_2 + ID_3; //set to continuous clock
        }
        else
        {
            TB0CTL = MC_0; //shut off clock
            TB0CCR0 = TB0R;//set each reg
            TBCTL = TBCLR;//clear timer
            TB0CTL=TBSSEL_1 + MC_1 + ID_3; //set back to up timer
            P1IES |=BIT1; //pos edge set
        }
        P1IFG &= ~BIT1; //clear flag
    }
