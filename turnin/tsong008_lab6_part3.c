/*	Author: Tinghui Song
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #6  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	
 *	Demo URL: 
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "Timer.h"

enum States {Start, Wait, Increment, Decrement, Reset} State;

unsigned char cnt = 7; //initial output PORTB
unsigned char counter = 0;//counter to count 1 second

void Tick()
{
    unsigned char tempA = ~PINA;
    switch(State){ //transitions
        case Start:
	    PORTB = cnt;
            State = Wait;
	    counter = 0;
            break;
        case Wait:
            if((tempA & 0x03) == 0x00){
                State = Wait;
		counter = 0;
            }
            else if((tempA & 0x03) == 0x01){
		counter = 0;
                State = Increment;
                if(cnt < 9)
                {
                    ++cnt;
                    PORTB = cnt;
                }
            }
            else if((tempA & 0x03) == 0x02){
                State = Decrement;
		counter = 0;
                if(cnt > 0){
                    --cnt;
                    PORTB = cnt;
                }
            }
            else{
		counter = 0;
                State = Reset;
                cnt = 0;
                PORTB = cnt;
            }
            break;
        case Decrement:
            if((tempA & 0x03) == 0x00){
		counter = 0;
                State = Wait;
            }
            else if((tempA & 0x03) == 0x01){
                State = Increment;
		counter = 0;	
                if(cnt < 9){
                    ++cnt;
                    PORTB = cnt;
                }
            }
            else if((tempA & 0x03) == 0x02){
                State = Decrement;
		if (counter ==10 ){
			counter = 0;
			if (cnt > 0){
				cnt--;
				PORTB = cnt;
			}
		}
            }
            else{
		counter = 0;
                State = Reset;
                cnt = 0;
                PORTB = cnt;
            }
            break;
        case Increment:
            if((tempA & 0x03) == 0x00){
                State = Wait;
		counter = 0;
            }
            else if((tempA & 0x03) == 0x01){
                State = Increment;
		if ( counter == 10 ){
			counter = 0;
			if ( cnt < 9){
				cnt++;
				PORTB = cnt;
			}
		}
            }
            else if((tempA & 0x03) == 0x02){
                State = Decrement;
		counter = 0;
                if(cnt > 0){
                    --cnt;
                    PORTB = cnt;
                }
            }
            else{
		counter = 0;
                State = Reset;
                cnt = 0;
                PORTB = cnt;
            }
            break;
        case Reset:
            if((tempA & 0x03) == 0x00){
		counter = 0;
                State = Wait;
            }
            else if((tempA & 0x03) == 0x01){
		counter = 0;
                State = Increment;
                if(cnt < 9){
                    ++cnt;
                    PORTB =  cnt;
                }
            }
            else if((tempA & 0x03) == 0x02){
		counter = 0;
                State = Decrement;
                if(cnt > 0)
                {
                    --cnt;
                    PORTB = cnt;
                }
            }

            else{
		counter = 0;
                State  = Reset;
                cnt = 0;
                PORTB = cnt;
            }
            break;
        default:
            State = Start;
            break;
    }
    switch(State){ //Actions
        case Start:
            PORTB =  cnt;
            break;
        case Wait:
            break;
        case Increment:
            break;
        case Decrement:
            break;
        case Reset:
            break;
        default:
            break;
    }
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
    /* Insert your solution below */
  	TimerSet(100);
 	TimerOn();
	State = Start;
 	while(1){
		Tick();
   	 	while(!TimerFlag);
   	 	TimerFlag = 0;
		counter++;
 	 }
}
