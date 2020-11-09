/*	Author: Tinghui Song
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #6  Exercise #2
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

enum State{Start, Seq_0, Seq_1, Seq_2, Seq_3, A0_Pressed, A0_Released, Wait} State;

unsigned char i = 0;

void Tick(){
	
	unsigned char tempA = ~PINA;

	switch(State){//Transitions
		case Start:
			State = Seq_0;
			break;
		case Seq_0:
			State = (tempA == 0x01)? A0_Pressed : Seq_1;
			break;
		case Seq_1:
			State = (tempA == 0x01)? A0_Pressed : Seq_2;
			break;
		case Seq_2:
			State = (tempA == 0x01)? A0_Pressed : Seq_3;
			break;
		case Seq_3:
			State = (tempA == 0x01)? A0_Pressed : Seq_0;
			break;
		case A0_Pressed:
			State = (tempA == 0x00)? A0_Released : A0_Pressed;
			break;
		case A0_Released:
			State = (tempA == 0x01)? Wait : A0_Released;
			break;
		case Wait:
			State = (tempA == 0x00)? Seq_0 : Wait;
			break;
		default:
			//State = Start;
			//printf(“reached default case\n”);
			break;
	}//Transitions
	
	switch(State){//Actions
		case Start:
			break;
		case Seq_0:
			i = 0;
			PORTB = 0x01;
			break;
		case Seq_1:
			i = 1;
			PORTB = 0x02;
			break;
		case Seq_2:
			i = 2;
			PORTB = 0x04;
			break;	
		case Seq_3:
			i = 1;
			PORTB = 0x02;
			break;
		case A0_Pressed:
			break;
		case A0_Released:
			if ( i == 0 ){
				PORTB = 0x01;}
			else if ( i == 1 ){
				PORTB = 0x02;}
			else if ( i == 2 ){
				PORTB = 0x04;}
			break;
		case Wait:
			break;
		default:
			//printf(“default case reached\n”);
			break;
	}//Actions

}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
    /* Insert your solution below */
  	TimerSet(300);
 	TimerOn();
	State = Start;
 	while(1){
		Tick();
   	 	while(!TimerFlag);
   	 	TimerFlag = 0;
 	 }
}
