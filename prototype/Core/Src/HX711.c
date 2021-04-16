/**
 *
 * HX711 library for Arduino
 * https://github.com/bogde/HX711
 *
 * Modified by: Hasib Arian <Hasib.arian@ryerson.ca>
 * For: MEC825 - CAPSTONE PROJECT
 *
 * MIT License
 * (c) 2018 Bogdan Necula
 *
**/


#include "HX711.h"
#include <stdint.h>
#include "stm32l4xx_hal.h"
#include <stdio.h>
#include <stdbool.h>


uint8_t shiftInSlow() {
    uint8_t value = 0;
    uint8_t i;
    for(i = 0; i < 8; ++i) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11,SET); //SCK HIGH
        HAL_Delay(1);
        value |= HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_10) << (7 - i);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11,RESET); //SCK LOW
        HAL_Delay(1);
    }
    return value;
}

void delay_us(uint8_t value){

	uint8_t i;
	for (i = value; i > 0; i--);
}

unsigned long readCount(){

	int ADDO = 1;
	int ADSK = 0;
	unsigned long count = 0;
	unsigned char i;
	int ii=0;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, RESET);

	while (1){

		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_10)==0)
				{
					delay_us(1);
					if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_10)==0)
					{
						break;
					}
				}

				ii++;
				if(ii>=1000000)
				{
					break;
				}
	}

		delay_us(1);
		for (i=0; i < 24; i++){
			ADSK = 1;
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, SET);
			delay_us(1);
			count = count << 1;
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, RESET);
			ADSK = 0;

			if (HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_10)==1){
				count++;
			}
		}


	ADSK = 1;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, SET);
	delay_us(2);
	count = count ^0x800000;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, RESET);
	return(count);


}


//setting the gain of the system
//----------------------
//void begin(int bytegain) {
//
//	set_gain(128); //set the gain of the loadcell!
//}
//
//void set_gain(int gain) {
//	switch (gain) {
//		case 128:		// channel A, gain factor 128
//			GAIN = 1;
//			break;
//		case 64:		// channel A, gain factor 64
//			GAIN = 3;
//			break;
//		case 32:		// channel B, gain factor 32
//			GAIN = 2;
//			break;
//	}
//
//}
//----------------------





//checking if load cell is ready
//----------------------
void wait_ready(unsigned long delay_ms) {
	// Wait for the chip to become ready.
	// This is a blocking implementation and will
	// halt the sketch until a load cell is connected.
	while (!is_ready()) {
		// Probably will do no harm on AVR but will feed the Watchdog Timer (WDT) on ESP.
		// https://github.com/bogde/HX711/issues/73
		HAL_Delay(delay_ms);
	}
}


bool is_ready() {
	return (HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_11) == 0);
}
//----------------------


long read() {

	// Wait for the chip to become ready.
	while(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_11) == 1){
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_11) == 0){
			break;
		}
	}

	// Define structures for reading data into.
	unsigned long value = 0;
	uint8_t data[3] = { 0 };
	uint8_t filler = 0x00;

	// Pulse the clock pin 24 times to read the data.
	data[2] = shiftInSlow();
	data[1] = shiftInSlow();
	data[0] = shiftInSlow();

	// Set the channel and the gain factor for the next reading using the clock pin.
	for (unsigned int i = 0; i < 128; i++) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, SET); //SCK HIGH

		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,RESET); //SCK LOW

	}

	// Replicate the most significant bit to pad out a 32-bit signed integer
	if (data[2] & 0x80) {
		filler = 0xFF;
	} else {
		filler = 0x00;
	}


	value = (unsigned long) filler << 24 ;
	value |= (unsigned long) data[2]<< 16;
	value |= (unsigned long) data[1] <<8;
	value |= (unsigned long) data[0]; //


	// Construct a 32-bit signed integer
//	value =( int(filler) << 24
//			| static_cast<unsigned long>(data[2]) << 16
//			| static_cast<unsigned long>(data[1]) << 8
//			| static_cast<unsigned long>(data[0]) );


  //%lu

	return (long) value;
}


long read_average(int times) {
	long sum = 0;
	for (int i = 0; i < times; i++) {
		sum += read();
		// Probably will do no harm on AVR but will feed the Watchdog Timer (WDT) on ESP.
		// https://github.com/bogde/HX711/issues/73
		HAL_Delay(0);
	}
	return sum / times;
}


