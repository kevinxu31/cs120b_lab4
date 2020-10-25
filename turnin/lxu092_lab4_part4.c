/*	Author: lxu092
 *  Partner(s) Name: Luofeng Xu
 *	Lab Section:022
 *	Assignment: Lab 4  Exercise 4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum States{Start,Locked,Pswd_P,Pswd_R,Unlocked,Pswd_Po,Pswd_Ro}state;
unsigned char A0;
unsigned char A1;
unsigned char A2;
unsigned char A7;
void Tick(){
	switch(state){
		case Start:
			PORTB=0x00;
			state=Locked;
			break;
		case Locked:
			PORTB=0x00;
			if(A2&(!A1)&(!A0)&(!A7)){state=Pswd_P;}
			else{state=Locked;}
			break;
		case Pswd_P:
			if((!A2)&(!A1)&(!A0)&(!A7)){state=Pswd_R;}
			else if(A2&(!A1)&(!A0)&(!A7)){state=Pswd_P;}
			else{state=Locked;}
			break;
                case Pswd_R:
                        if((!A2)&(!A1)&(!A0)&(!A7)){state=Pswd_R;}
                        else if((!A2)&(A1)&(!A0)&(!A7)){state=Unlocked;PORTB=0x01;}
                        else {state=Locked;}
                        break;
		case Unlocked:
			if((!A2)&(!A1)&(!A0)&(A7)){state=Locked;PORTB=0x00;}
			else if(A2&(!A1)&(!A0)&(!A7)){state=Pswd_Po;}
			else {state=Unlocked;}
			break;
		case Pswd_Po:
			if((!A2)&(!A1)&(!A0)&(!A7)){state=Pswd_Ro;}
			else if(A2&(!A1)&(!A0)&(!A7)){state=Pswd_Po;}
			else {state=Unlocked;}
			break;
		case Pswd_Ro:
			if((!A2)&(!A1)&(!A0)&(!A7)){state=Pswd_Ro;}
                        else if((!A2)&(A1)&(!A0)&(!A7)){state=Locked;PORTB=0x00;}
                        else {state=Unlocked;}
                        break;

			
		default:
			break;
	}
}

int main(void) {
    DDRA=0x00;PORTA=0xFF;
    DDRB=0xFF;PORTB=0x00;       
    state=Start;
    while (1) {
	A0=PINA&0x01;
	A1=(PINA>>1)&0x01;
	A2=(PINA>>2)&0x01;
	A7=(PINA>>7)&0x01;
	Tick();
    }
    return 1;
}

