/*	Author: lxu092
 *  Partner(s) Name: Luofeng Xu
 *	Lab Section:022
 *	Assignment: Lab 4  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum States{Start,Init,Press,Release}state;
unsigned char b0=1;
unsigned char b1=0;
unsigned char A0;
void Tick(){
	switch(state){
		case Start:
			state=Init;
			break;
		case Init:
			if(A0){
				state=Press;
			}
			break;
		case Press:
			if(A0){state=Press;}
			else if(!A0){state=Release;}
			break;
		case Release:
			if(!A0){state=Release;}
			else if(A0) {state=Press;}
			break;
		default:
			break;
	}
	switch(state){
                case Start:
                        break;
                case Init:
			PORTB=0x01;
                        break;
                case Press:
			if(PORTB==0x01){PORTB=0x02;}
			else {PORTB=0x01;}
                        break;
                case Release:
                        break;
                default:
                        break;
	}
}



int main(void) {
    DDRA=0x00;PORTA=0xFF;
    DDRB=0xFF;PORTB=0x00;       
    state=Start;
    PORTB=0x01;
    while (1) {
	A0=PINA&0x01;
	Tick();	

    }
    return 1;
}
