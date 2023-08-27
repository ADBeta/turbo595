/*******************************************************************************
* turbo595 is a library to allow extremely fast communication with 74xx595 Shift
* Registers, using chASM2 to control the hardware layer.
*
* ADBeta 
*******************************************************************************/
#include <Arduino.h>

#include "chASM2.h"
#include "turbo595.h"

/*** Static / Hidden variabes & Functions *************************************/

//This can be leveraged to write n bits, e.g. 6bit bytes 
static void tx_bit(turbo595_t *dev, bool bit)
{
	chasm_write(&dev->p_DAT, bit);
	
	//Cycle SCLK pin
	chasm_write(&dev->p_SCLK, HIGH);
	chasm_write(&dev->p_SCLK, LOW);
}

static void latch(turbo595_t *dev)
{
	chasm_write(&dev->p_RCLK, HIGH);
	chasm_write(&dev->p_RCLK, LOW);
}

/** Initialization ************************************************************/
void turbo595_init(turbo595_t *dev, 
                   uint8_t prm_SCLK, uint8_t prm_RCLK, uint8_t prm_DAT)
{
	//Initialise each static chasm_t to the passed pins 
	chasm_init(&dev->p_SCLK, prm_SCLK);
	chasm_init(&dev->p_RCLK, prm_RCLK);
	chasm_init(&dev->p_DAT, prm_DAT);
	
	//Set the pin mode to output
	chasm_setmode(&dev->p_SCLK, OUTPUT);
	chasm_setmode(&dev->p_RCLK, OUTPUT);
	chasm_setmode(&dev->p_DAT, OUTPUT);
	
	//Set the pins LOW to initialise a known state
	chasm_write(&dev->p_SCLK, LOW);
	chasm_write(&dev->p_RCLK, LOW);
	chasm_write(&dev->p_DAT, LOW);
}

/** Write functions ***********************************************************/
//Write 1 byte to the Shift Register.
void turbo595_write_byte(turbo595_t *dev,uint8_t b) {
	//8Bits is the chASM write() max depth, so setting a bit and checking is not
	//needed here. This will be the fastest function (as expected anyway).
	for(uint8_t cBit = 0; cBit < 8; cBit++) {
		//TX The current bit
		tx_bit(dev, b & 0x80);
		//Shift the next bit into the mask position.
		b = b << 1;
	}
	
	latch(dev);
}

//Write a 2 byte int to the Shift Register.
void turbo595_write_int(turbo595_t *dev, uint16_t i) {
	//This function uses a bit depth greater than chASMs' write() can handle.
	//To get around this, set a flag bit based on the MSB of the value passed.
	for(uint8_t bit_sent = 0; bit_sent < 16; bit_sent++) {
		//If the MSB is 1, set the cBit to 1, to fit chASM2s bit depth.
		bool cBit = 0;
		if(i & 0x8000) cBit = 1;
		
		//TX The current bit
		tx_bit(dev, cBit);
		//Shift the next bit into the mask position.
		i = i << 1;
	}

	latch(dev);
}

//Write a 4 byte long to the Shift Register.
void turbo595_write_long(turbo595_t *dev, uint32_t l) {
	//This function uses a bit depth greater than chASMs' write() can handle.
	//To get around this, set a flag bit based on the MSB of the value passed.
	for(uint8_t bit_sent = 0; bit_sent < 32; bit_sent++) {
		//If the MSB is 1, set the cBit to 1, to fit chASM2s bit depth.
		bool cBit = 0;
		if(l & 0x800000) cBit = 1;
		
		//TX The current bit
		tx_bit(dev, cBit);
		//Shift the next bit into the mask position.
		l = l << 1;
	}
	
	latch(dev);
}

//Write an array of arbitrary size to the Shift Register.
void turbo595_write_array(turbo595_t *dev, uint8_t* arr, uint16_t n) {
	uint8_t curr_byte = 0;
	//Go through all passed bytes
	for(uint16_t cByte = 0; cByte < n; cByte++) {
		curr_byte = arr[cByte];
	
		//Go through all bits in the byte
		for(uint8_t cBit = 0; cBit < 8; cBit++) {
			//TX The current bit
			tx_bit(dev, curr_byte & 0x80);
			//Shift the next bit into the mask position.
			curr_byte = curr_byte << 1;
		}
	}
	
	latch(dev);
}
