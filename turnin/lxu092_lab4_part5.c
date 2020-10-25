/*	Author: lxu092
 *  Partner(s) Name: Luofeng Xu
 *	Lab Section:022
 *	Assignment: Lab 4  Exercise 5
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum States{Start,Locked,Pswd_P,Pswd_R,R_1,R_2,R_3,R_4,Unlocked,Pswd_Po,Pswd_Ro,Ro_1,Ro_2,Ro_3,Ro_4}state;
unsigned char A0;
unsigned char A1;
unsigned char A2;
unsigned char A7;
char key[3]={1,2,1};
char pwd[3]={0,0,0};
unsigned char i;
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
			else if((!A2)&(!A1)&(A0)&(!A7)){state=R_1;}
			else {state=Locked;}    
                        break;
		case R_1:
			if((!A2)&(!A1)&(!A0)&(!A7)){state=R_2;}
			else{state=Locked;}
			break;
		case R_2:
			if((!A2)&(A1)&(!A0)&(!A7)){state=R_3;}
			else{state=Locked;}
			break;
		case R_3:
			if((!A2)&(!A1)&(!A0)&(!A7)){state=R_4;}
			else{state=Locked;}
			break;
		case R_4:
			if((!A2)&(!A1)&(A0)&(!A7)){state=Unlocked;PORTB=0x01;}
			else{state=Locked;}
			break;
		case Unlocked:
			PORTB=0x01;
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
                        else if((!A2)&(!A1)&(A0)&(!A7)){state=Ro_1;}
                        else {state=Unlocked;}
                        break;
		case Ro_1:
                        if((!A2)&(!A1)&(!A0)&(!A7)){state=Ro_2;}
                        else{state=Unlocked;}
                        break;
                case Ro_2:
                        if((!A2)&(A1)&(!A0)&(!A7)){state=Ro_3;}
                        else{state=Unlocked;}
                        break;
                case Ro_3:
                        if((!A2)&(!A1)&(!A0)&(!A7)){state=Ro_4;}
                        else{state=Unlocked;}
                        break;
                case Ro_4:
                        if((!A2)&(!A1)&(A0)&(!A7)){state=Locked;PORTB=0x00;}
                        else{state=Unlocked;}
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

