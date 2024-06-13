#include <LPC21xx.H>

#include "uart.h"
#include "servo.h"
#include "command_decoder.h"
#include "string.h"
#include "timer_interrupts.h"
#include "ADC.h"

#define NULL '\0'

void DisplayADCValue(unsigned int uiADCValue){
	
	char cTransmiterString[20] = "";

	AppendUIntToString(uiADCValue,cTransmiterString);
	AppendString("\n", cTransmiterString);
	Transmiter_SendString(cTransmiterString);
}


int main(){
	
	unsigned int uiADCValue;
	ServoInit(15000);
	UART_InitWithInt(9600);
	ADCInit();
	while(1){
		if(Transmiter_GetStatus()==FREE){
			uiADCValue=ADCRead(0);
			DisplayADCValue(uiADCValue);
			ServoGoTo(uiADCValue/21);
		}
	}
}
