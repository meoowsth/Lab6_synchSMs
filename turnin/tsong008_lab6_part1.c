/*	Author: Tinghui Song
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #6  Exercise #1
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

enum State{Start, PB_0, PB_1, PB_2} State;

void Tick(){

	switch(State){//Transitions
		case Start:
			State = PB_0;
			break;
		case PB_0:
			State = PB_1;
			break;
		case PB_1:
			State = PB_2;
			break;
		case PB_2:
			State = PB_0;
			break;
		default:
			State = Start;
			//printf(“reached default case\n”);
			break;
	}//Transitions
	
	switch(State){//Actions
		case Start:
			break;
		case PB_0:
			PORTB = 0x01;
			break;
		case PB_1:
			PORTB = 0x02;
			break;
		case PB_2:
			PORTB = 0x04;
			break;	
		default:
			//printf(“default case reached\n”);
			break;
	}//Actions

}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
  	TimerSet(1000);
 	TimerOn();
	State = Start;
 	while(1){
		Tick();
   	 	while(!TimerFlag);
   	 	TimerFlag = 0;
 	 }
}
