#include <LPC21xx.H>
#include "ADC.h"

#define mAIN0_ON_P0_27					0x00400000
#define mADC_Operational				0x00200000
#define mClockRate_11						0x00000400

#define mConvertion_Done 				0x80000000
#define mConvertion_Start_Now 	0x01000000
#define mFirst_Ten_Bits					0x000003FF


void ADCInit(){
	PINSEL1 = PINSEL1 | mAIN0_ON_P0_27;  // Ustawienie Pinu
	ADCR = mADC_Operational | mClockRate_11; 
}

unsigned int ADCRead(unsigned char ucChannelNumber){

	unsigned int uiResult = 0;
	
	ADCR |= (1<<ucChannelNumber); // wybór kanaBu
	ADCR |= mConvertion_Start_Now; //start konwersji
	
	while((ADDR & mConvertion_Done) == 0){ 
	}
	
	ADCR ^= ((1<<ucChannelNumber) | mConvertion_Start_Now); 
	uiResult = ((ADDR >> 6) & mFirst_Ten_Bits);
	return uiResult;
}