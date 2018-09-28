#include <msp430.h>


/**
 * main.c
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

       //IN/OUT INFO
        P1DIR |= BIT0;
        P1REN |= BIT3;
        P1OUT |= BIT0;
        P1OUT |= BIT3;


        //INTERRUPT INFO
        P1IE |= BIT3; // enables interupt for button
        P1IES |= BIT3;  //pos edge trigger for button
        CCTL0 = CCIE; // enables interrupt for counting regs
        CCR0 =  500;   //sets initial freuency
        TACTL = TASSEL_1 + MC_1 + ID_3;   //makes timer in up mode
        _BIS_SR(LPM0_bits + GIE); //global interrupt enable







}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0 (void)
{
    P1OUT ^=BIT0; //toggles P1.0
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if(P1IES & BIT3) // if button is pressed
    {
      TACTL = TACLR; //clear timer
      TACTL = TASSEL_1 + MC_2 + ID_3; //make timer continuous
      P1IES &= ~BIT3; //pos edge trigger
}
else
{
    CCR0 = TA0R; //sets CCR0 frequency to value kept in TA0 register
            TACTL = TASSEL_1 + MC_1 + ID_3; //change timer back to up mode
            P1IES |= BIT3; //neg edge trigger

}
P1IFG &= ~BIT3; //flag reset on button
}




